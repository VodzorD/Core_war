/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:05:32 by jpasty            #+#    #+#             */
/*   Updated: 2021/02/12 15:16:59 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static uint8_t		*validate_code(int fd, uint32_t prog_size)
{
	uint8_t			*code;
	uint8_t			eof;

	if (!(code = malloc(sizeof(uint8_t) * prog_size)))
		return (NULL);
	if (read(fd, code, prog_size) != prog_size)
		return (NULL);
	if (read(fd, &eof, 1) != 0)
		return (NULL);
	return (code);
}

static char			*validate_str(uint8_t **bytes, size_t len)
{
	char			*ret;
	size_t			i;
	size_t			offset;

	i = 0;
	offset = len;
	while (i < 4)
		if ((*bytes)[len + i++] != 0)
			return (NULL);
	if (!(ret = malloc(sizeof(char) * len)))
		return (NULL);
	while (len--)
		ret[len] = (*bytes)[len];
	*bytes += (offset + 4);
	return (ret);
}

static uint32_t		validate_num(uint8_t **bytes, size_t size)
{
	uint32_t		num;
	size_t			i;

	num = 0x00;
	i = 0;
	if (size > sizeof(uint32_t))
		return (0);
	if (*bytes[0] == 0xff)
		return (CHAMP_MAX_SIZE + 1);
	while ((*bytes)[i] == 0x00)
		if (i++ >= size)
			return (-1);
	while (i < size)
	{
		num += (*bytes)[i];
		if (++i < size)
			num <<= 8;
	}
	*bytes += size;
	return (num);
}

static t_player		*check_plr(size_t id, int fd)
{
	static uint8_t	hdr[sizeof(t_header)];
	t_player		*plr;
	uint8_t			*hdd;

	hdd = hdr;
	ft_bzero(hdr, sizeof(t_header));
	plr = create_player(id);
	if (read(fd, hdr, sizeof(t_header)) != sizeof(t_header))
		ft_error("reading error", -1);
	if (validate_num(&hdd, sizeof(COREWAR_EXEC_MAGIC)) != COREWAR_EXEC_MAGIC)
		ft_error("MAGIC doesn't exist!", -1);
	if (!(plr->name = validate_str(&hdd, PROG_NAME_LENGTH)))
		ft_error("Champ name error!", -1);
	if ((plr->code_size = validate_num(&hdd, sizeof(uint32_t)))
			> CHAMP_MAX_SIZE)
		ft_error("Wrong code size!", -1);
	if (!(plr->comment = validate_str(&hdd, COMMENT_LENGTH)))
		ft_error("Champ comment error!", -1);
	if (!(plr->code = validate_code(fd, plr->code_size)))
		ft_error("Code doesn't match code size", -1);
	return (plr);
}

void				champ_validation(t_args *args, t_lst *plrs)
{
	int				i;
	int				fd;

	i = 0;
	while (i < args->count_players)
	{
		if ((fd = open(args->players[i], O_RDONLY)) == -1)
			ft_error("Cannot open file", -1);
		lst_prepend(plrs, check_plr(i + 1, fd));
		close(fd);
		i++;
	}
	lst_sort(plrs, (t_fcompare)player_cmp);
}
