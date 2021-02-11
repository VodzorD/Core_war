/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:40:57 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:40:59 by cshinoha         ###   ########.fr       */
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
