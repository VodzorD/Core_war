/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:54:12 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 15:16:13 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		player_intro(t_player *player)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		player->id,
		player->code_size,
		player->name,
		player->comment);
}

void			print_intro(t_vm *vm)
{
	ft_printf("Introducing contestants...\n");
	lst_foreach(&vm->players, (t_fmap)player_intro);
}

inline void		print_awards(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
													vm->last_alive->id,
													vm->last_alive->name);
}

void			print_arena(uint8_t *arena)
{
	int			i;
	int			j;
	t_str_bld	*bld;

	bld = sb_create(NULL);
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_sbprintf(bld, "%.4p : ", i);
		j = 0;
		while (j < 32)
		{
			ft_sbprintf(bld, "%.2x ", arena[i + j]);
			j++;
		}
		ft_sbprintf(bld, "\n");
		i += 32;
	}
	write(1, sb_concat(bld), bld->len);
	sb_free(bld);
}