/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:25:12 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:26:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			move_cursor(t_cursor *cursor)
{
	cursor->offset = calc_addr(cursor->offset + cursor->step);
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}

uint32_t		step_size(uint8_t arg_type, t_op *op)
{
	if (arg_type & T_REG)
		return (REG_LEN);
	else if (arg_type & T_DIR)
		return (op->t_dir_size);
	else if (arg_type & T_IND)
		return (IND_SIZE);
	return (0);
}

uint32_t		calc_step(t_cursor *cursor)
{
	int32_t		i;
	uint32_t	step;

	i = 0;
	step = 0;
	step += OP_CODE_LEN + cursor->op->args_types_code * ARGS_CODE_LEN;
	while (i < cursor->op->args_num)
	{
		step += step_size(cursor->args_types[i], cursor->op);
		i++;
	}
	return (step);
}
