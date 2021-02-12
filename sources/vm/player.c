/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:14:28 by jpasty            #+#    #+#             */
/*   Updated: 2021/02/11 23:14:28 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*create_player(int id)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		ft_error("ERR_PLAYER_INIT", -1);
	player->id = id;
	return (player);
}

void		dstr_player(t_player *player)
{
	if (player)
	{
		free(player->name);
		free(player->comment);
		free(player->code);
		free(player);
	}
}

int8_t		check_player_filename(char *filename)
{
	char	*ext;

	ext = ft_strchr(filename, '.');
	if (*filename != '.' && ext)
		if (!ft_strcmp(ext, ".cor"))
			return (1);
	return (0);
}

int32_t		count_plrs(char **av)
{
	int32_t	plrs_num;

	plrs_num = 0;
	while (*av)
	{
		if (ft_strendwith(".cor", *av))
			plrs_num++;
		av++;
	}
	return (plrs_num);
}
