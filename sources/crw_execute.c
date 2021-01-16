/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:43:07 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/15 16:18:52 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	update_op(t_vm *vm, t_cursor *current)
{
	uint8_t code;

	code = vm->arena[current->pc];
	if (code >= 0x01 && code <= 0x10)
	{
		current->op = &g_op[code];
		current->till_exec = current->op->cycles;
	}
}

void	move_cursor(t_vm *vm, t_cursor *cursor)
{
	if (vm->vs)
		clear_cursor(vm, cursor);
	cursor->pc += cursor->step;
	cursor->pc = calc_addr(cursor->pc);
	if (vm->vs)
		draw_cursor(vm, cursor);
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}

static void	exec_op(t_cursor *cursor, t_vm *vm)
{
	if (!cursor->till_exec)
		update_op(vm, cursor);
	if (cursor->till_exec)
		cursor->cycles_to_exec--;
	if (!cursor->till_exec)
	{
		if (cursor->op)
		{
			parse_types_code(vm, cursor, op);
			if (is_arg_types_valid(cursor, op) && is_args_valid(cursor, vm, op))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
		}
		else
			cursor->step = OP_CODE_LEN;
		move_cursor(vm, cursor);
	}
}

void		exec_cycle(t_vm *vm)
{
	t_itr	itr;

	qu_itr_load(vm->cycles, &itr, NULL);
	vm->cycles++;
	vm->cycles_after_check++;
	while (itr_has_next(itr))
		exec_op(itr_next(itr), vm);
	itr_clear(&itr);
}

void			*crw_exec(t_vm *vm)
{
	while (!qu_is_empty(vm->cursors))
	{
		if (vm->dump_cycle == vm->cycles)
		{
			print_arena(vm->arena, vm->dump_print_mode);
			exit(0);
		}
		if (vm->show_cycle > 0 && !(vm->cycles % vm->show_cycle))
			print_arena(vm->arena, vm->show_print_mode);
		exec_cycle(vm);
		if (vm->cycles_to_die == vm->cycles_after_check
			|| vm->cycles_to_die <= 0)
			cycles_to_die_check(vm);
	}

//	TODO
}