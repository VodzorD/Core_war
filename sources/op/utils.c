/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:00:24 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:03:25 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int32_t		bytecode_to_int32(const uint8_t *arena, int32_t addr, int32_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = (arena[calc_addr(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((arena[calc_addr(addr + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += arena[calc_addr(addr + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void		int32_to_bytecode(uint8_t *arena, int32_t addr, int32_t value,
						int32_t size)
{
	int8_t i;

	i = 0;
	while (size)
	{
		arena[calc_addr(addr + size - 1)] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int32_t		get_op_arg(t_cursor *cursor, uint8_t index, int mod)
{
	int32_t		value;

	value = 0;
	if (cursor->args_types[index] <= 4
			&& g_arg_hands[cursor->args_types[index]])
		value = g_arg_hands[cursor->args_types[index]](cursor, mod);
	cursor->step += step_size(cursor->args_types[index], cursor->op);
	return (value);
}
