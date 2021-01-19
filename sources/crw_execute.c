/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:43:07 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/19 20:34:52 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		update_op(t_cursor *current)
{
	uint8_t		code;

	if (!cursor->till_exec)
	{
		code = current->vm->arena[current ->offset];
		current->op = NULL;
		if (code >= 0x01 && code <= 0x10)
		{
			current->op = &g_op[code];
			current->till_exec = current->op->cycles - 1;
		}
	}
	else if (cursor->till_exec)
		cursor->till_exec--;
	return cursor->till_exec;
}


static void	exec_op(t_cursor *cursor)
{
	if (update_op(cursor))
		return ;
	if (cursor->op)
	{
		parse_types_code(cursor);
		if (is_arg_types_valid(cursor) && is_args_valid(cursor))
			op->func(cursor);
		else
			cursor->step += calc_step(cursor, op);
	}
	else
		cursor->step = OP_CODE_LEN;
	move_cursor(cursor);

}

static void		exec_cycle(t_vm *vm)
{
	t_itr	itr;

	qu_itr_load(vm->cursors, &itr, NULL);
	vm->cycles++;
	vm->cycles_after_check++;
	itr_foreach(&itr, &exec_op)
//	while (itr_has_next(&itr))
//		exec_op(itr_next(&itr), vm);
	itr_clear(&itr);
}

void			*crw_exec(t_vm *vm)
{
	while (!qu_is_empty(vm->cursors))
	{
		exec_cycle(vm);
		if (vm->cycles_to_die <= vm->cycles_after_check
//			|| vm->cycles_to_die <= 0
			)
			cycles_to_die_check(vm);
	}

}