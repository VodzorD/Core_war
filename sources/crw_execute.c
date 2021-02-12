/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:35:57 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 19:23:44 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		update_op(t_cursor *cursor)
{
	uint8_t		code;

	if (!cursor->till_exec)
	{
		code = cursor->vm->arena[cursor->offset];
		cursor->op = NULL;
		if (code >= 0x01 && code <= 0x10)
		{
			cursor->op = &g_op[code];
			cursor->till_exec = cursor->op->cycles;
		}
		else
			cursor->op = NULL;
	}
	if (cursor->till_exec)
		cursor->till_exec--;
	return (cursor->till_exec);
}

static void		exec_op(t_cursor *cursor)
{
	if (update_op(cursor))
		return ;
	if (cursor->op)
	{
		parse_types_code(cursor);
		if (is_arg_types_valid(cursor) && is_args_valid(cursor))
			cursor->op->func(cursor);
		else
			cursor->step += calc_step(cursor);
		cursor->op = NULL;
	}
	else
		cursor->step = OP_CODE_LEN;
	move_cursor(cursor);
}

static void		exec_cycle(t_vm *vm)
{
	t_node		*node;

	node = vm->cursors.tail;
	vm->cycles++;
	vm->cycles_after_check++;
	while (node)
	{
		exec_op(node->data);
		node = node->prev;
	}
}

void			crw_exec(t_vm *vm)
{
	while (!qu_is_empty(&vm->cursors))
	{
		if (vm->arg.dump_cycle && vm->cycles == vm->arg.dump_cycle)
		{
			print_arena(vm->arena);
			exit(0);
		}
		exec_cycle(vm);
		if (vm->cycles_to_die <= vm->cycles_after_check
			|| vm->cycles_to_die <= 0)
			cycles_to_die_check(vm);
	}
}
