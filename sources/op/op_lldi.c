/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:59:52 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:07:51 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void				op_lldi(t_cursor *cursor)
{
	int32_t	addr_1;
	int32_t	addr_2;
	int32_t	reg;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	addr_1 = get_op_arg(cursor, 0, 1);
	addr_2 = get_op_arg(cursor, 1, 1);
	reg = get_byte(cursor->vm, cursor->offset + cursor->step);
	cursor->reg[reg - 1] = bytecode_to_int32(cursor->vm->arena,
			cursor->offset + (addr_1 + addr_2), DIR_SIZE);
	cursor->step += REG_LEN;
}
