/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:58:50 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:06:06 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		op_aff(t_cursor *cursor)
{
	int32_t	reg;
	int32_t	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = get_byte(cursor->vm, cursor->offset + cursor->step);
	value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
//	if (cursor->vm->display_aff)
//		ft_printf("Aff: %c\n", (char)value); TODO
}
