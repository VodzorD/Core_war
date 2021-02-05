/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:36:43 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/05 20:03:33 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_cursor	*create_cursor(t_player *player, int32_t offset, t_vm *vm)
{
	t_cursor		*cursor;
	static uint32_t	cursor_id;

	if (!(cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		ft_error("ERR_CURSOR_INIT", 1);
	cursor->id = ++cursor_id;
	cursor->offset = offset;
	cursor->reg[0] = -(player->id);
	cursor->player = player;
	cursor->vm = vm;
	return (cursor);
}

t_cursor		*clone_cursor(t_cursor *cursor)
{
	t_cursor	*new;

	new = create_cursor(cursor->player, cursor->offset, cursor->vm);
	ft_memcpy(new->reg, cursor->reg, sizeof cursor->reg);
	new->carry = cursor->carry;
	new->last_live = cursor->last_live;
	return (new);
}

