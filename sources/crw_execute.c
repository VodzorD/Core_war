#include "../includes/corewar.h"

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
//			ft_printf("Set op %s cursor %u\n", cursor->op->name, cursor->id);
		} else
			cursor->op = NULL;
	}
	if (cursor->till_exec)
		cursor->till_exec--;
	return cursor->till_exec;
}

void	print_state(t_vm *vm)
{
	t_node *node;
	t_cursor *cursor;
	node = vm->cursors.head;
	while (node)
	{
		cursor = node->data;
//		ft_printf("CUR id-%u till-%u offset-%u last_live-%u step-%u carry-%s op-%s\n",
//			cursor->id, cursor->till_exec, cursor->offset, cursor->last_live, cursor->step, cursor->carry ? "TRUE" : "false", cursor->op ? cursor->op->name : "____");
		node = node->next;
	}
}

static void	exec_op(t_cursor *cursor)
{
	int i = 0;
	if (update_op(cursor))
		return ;
//	if (cursor->vm->cycles == 2495) {
//		print_state(cursor->vm);
//		exit(0);
//	}
//	else if()
//		exit(0);
//	if (cursor->vm->cycles == 860 && cursor->id == 2)
//	{
//		while (i < MEM_SIZE)
//			ft_printf("%u   %X\n", i,bytecode_to_int32(cursor->vm->arena, i++, 1));
//	}
//		write(1, &cursor->vm->arena, MEM_SIZE);
	if (cursor->op)
	{
		parse_types_code(cursor);
		if (is_arg_types_valid(cursor) && is_args_valid(cursor))
		{
//			if (cursor->vm->cycles > 8000)
//			ft_printf("cycles: %u curs: %u func: %s\n", cursor->vm->cycles, cursor->id, cursor->op->name);
			cursor->op->func(cursor);
		}
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
	t_itr	itr;

	ft_bzero(&itr, sizeof(t_itr));
	qu_itr_load(&vm->cursors, &itr, NULL);
	vm->cycles++;
	vm->cycles_after_check++;
	itr_foreach(&itr, (t_fmap)&exec_op);
	itr_clear(&itr);
}

void			crw_exec(t_vm *vm)
{
	while (!qu_is_empty(&vm->cursors))
	{
		exec_cycle(vm);
		if (vm->cycles_to_die <= vm->cycles_after_check
			|| vm->cycles_to_die <= 0
			)
			cycles_to_die_check(vm);
	}

}