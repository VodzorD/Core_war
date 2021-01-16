void				op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int32_t addr;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(vm, cursor, 1, true);
	if (cursor->carry)
	{
		if (vm->vs)
			clear_cursor(vm, cursor);
		cursor->pc = calc_addr(cursor->pc + (addr % IDX_MOD));
		if (vm->vs)
			draw_cursor(vm, cursor);
		cursor->step = 0;
	}
	if (vm->log & OP_LOG)
		log_zjmp(cursor, addr);
}
