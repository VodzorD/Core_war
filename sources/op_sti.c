/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:00:04 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:03:25 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void				op_sti(t_cursor *cursor)
{
	int32_t	reg;
	int32_t	value;
	int32_t	addr_1;
	int32_t	addr_2;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	reg = get_byte(cursor->vm, cursor->offset + cursor->step);
	value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
	addr_1 = get_op_arg(cursor, 1, 1);
	addr_2 = get_op_arg(cursor, 2, 1);
	int32_to_bytecode(cursor->vm->arena,
			(cursor->offset + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
}
