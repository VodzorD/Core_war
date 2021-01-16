/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:29:23 by jpasty            #+#    #+#             */
/*   Updated: 2021/01/16 20:34:03 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player	check_plr(size_t id, char *plr_filename);
static uint32_t	validate_magic(uint8_t *buff, size_t len);

int				champ_validation(t_lst *corewar_args)
{
	t_pair		*pair;
	t_lst		*plrs;
	t_itr		*cross = lst_itr_load(corewar_args, NULL, NULL);

	pair = NULL;
	while ((pair = itr_next(cross)))
		lst_prepend(lst,
			  check_plr((size_t) pair->key, pair->value, sizeof(header_t)));

	return (EXIT_SUCCESS);
}

static t_player	check_plr(size_t id, char *plr_filename, size_t header_size)
{
	t_player	*plr;
	int 		fd;
	int 		ret;
	uint8_t 	buff[header_size];
	header_t	*hdr;

	hdr = ft_memalloc(sizeof(header_t *));
	if (!(plr = ft_memalloc(sizeof(t_player*))))
		ft_error("Alloc err", -1);
	plr->id = id;
	if ((fd = open(plr_filename, O_RDONLY)) == -1)
		ft_error("Cannot open file", -1);
	if ((ret = read(fd, buff, header_size)) != header_size)
		ft_error("reading error", -1);
	if (validate_magic(buff, sizeof(COREWAR_EXEC_MAGIC)) != COREWAR_EXEC_MAGIC)
		ft_error("MAGIC doesn't exist!");
	if
	hdr->prog_name =

}

static uint32_t	validate_magic(uint8_t *buff, size_t len)
{
	uint32_t magic;
	int i;

	magic = 0x0;
	while (i < len)
	{
		magic += buff[i++];
		magic<<8;
	}
	return magic;
}