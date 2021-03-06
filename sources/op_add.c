/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:58:44 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 17:51:37 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_add(t_cursor *cursor)
{
	int32_t	reg1;
	int32_t	reg2;
	int32_t	reg3;
	int32_t	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg1 = get_byte(cursor->vm, cursor->offset + cursor->step);
	cursor->step += REG_LEN;
	reg2 = get_byte(cursor->vm, cursor->offset + cursor->step);
	cursor->step += REG_LEN;
	value = cursor->reg[reg1 - 1] + cursor->reg[reg2 - 1];
	cursor->carry = !value;
	reg3 = get_byte(cursor->vm, cursor->offset + cursor->step);
	cursor->reg[reg3 - 1] = value;
	cursor->step += REG_LEN;
}
