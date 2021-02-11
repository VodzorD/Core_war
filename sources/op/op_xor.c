/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:00:11 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:03:25 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void				op_xor(t_cursor *cursor)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	reg;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	value_1 = get_op_arg(cursor, 0, 1);
	value_2 = get_op_arg(cursor, 1, 1);
	value = value_1 ^ value_2;
	cursor->carry = !value;
	reg = get_byte(cursor->vm, cursor->offset + cursor->step);
	cursor->reg[reg - 1] = value;
	cursor->step += REG_LEN;
}
