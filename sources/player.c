/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:38:39 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/15 15:38:39 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_player	*create_player(int id)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		ft_error(ERR_PLAYER_INIT);
	player->id = id;
	return (player);
}