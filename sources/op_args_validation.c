/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_args_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:47:03 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/02 13:52:52 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/corewar.h"

static int		is_register(t_vm *vm, int32_t offset)
{
	int8_t r_id;

	r_id = get_byte(vm, offset);
	return (r_id >= 1 && r_id <= REG_NUMBER);
}

int				is_args_valid(t_cursor *cursor)
{
	int32_t		i;
	uint32_t	step;

	i = 0;
	step = OP_CODE_LEN + cursor->op->args_types_code * ARGS_CODE_LEN;
	while (i < cursor->op->args_num)
	{
		if ((cursor->args_types[i] == T_REG)
			&& !is_register(cursor->vm, cursor->offset + step))
			return (0);
		step += step_size(cursor->args_types[i], cursor->op);
		i++;
	}
	return (1);
}

int			is_arg_types_valid(t_cursor *cursor)
{
	int32_t i;

	i = 0;
	while (i < cursor->op->args_num)
	{
		if (!(cursor->args_types[i] & cursor->op->args_types[i]))
			return (0);
		i++;
	}
	return (1);
}

//inline int 			is_arg_types_valid(t_cursor *cursor) //TODO check
//{
//	return !(ft_memcmp(cursor->args_types, cursor->op->args_types,
//					   sizeof(uint8_t) * cursor->op->args_num));
//}

void		parse_types_code(t_cursor *cursor)
{
	int8_t args_types_code;

	if (cursor->op->args_types_code)
	{
		args_types_code = get_byte(cursor->vm, cursor->offset + 1);
		if (cursor->op->args_num >= 1)
			cursor->args_types[0] = g_arg_code[((args_types_code & 0xC0) >> 6) - 1];
		if (cursor->op->args_num >= 2)
			cursor->args_types[1] = g_arg_code[((args_types_code & 0x30) >> 4) - 1];
		if (cursor->op->args_num >= 3)
			cursor->args_types[2] = g_arg_code[((args_types_code & 0xC) >> 2) - 1];
	}
	else
		cursor->args_types[0] = cursor->op->args_types[0];
}