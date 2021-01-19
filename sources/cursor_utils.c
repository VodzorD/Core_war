/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:48:38 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/19 18:48:38 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./incledes/corewar.h"

void	move_cursor(t_cursor *cursor)
{
	cursor ->offset = (cursor ->offset + cursor->step) % MEM_SIZE;
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}


uint32_t	step_size(uint8_t arg_type, t_op *op)
{
	if (arg_type & T_REG)
		return (REG_LEN);
	else if (arg_type & T_DIR)
		return (op->t_dir_size);
	else if (arg_type & T_IND)
		return (IND_SIZE);
	return (0);
}