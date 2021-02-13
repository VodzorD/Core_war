/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:58:55 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 17:54:35 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_fork(t_cursor *cursor)
{
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	new = clone_cursor(cursor);
	new->offset = calc_addr(cursor->offset
						+ get_op_arg(cursor, 0, 1) % IDX_MOD);
	qu_push_head(&cursor->vm->cursors, new);
}
