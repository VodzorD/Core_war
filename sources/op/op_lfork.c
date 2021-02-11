/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:59:36 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:02:06 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void				op_lfork(t_cursor *cursor)
{
	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(cursor, 0, 1);
	new = clone_cursor(cursor);
	new->offset = calc_addr(addr + cursor->offset);
	qu_push_head(&cursor->vm->cursors, new);
}
