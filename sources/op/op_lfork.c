void				op_lfork(t_vm *vm, t_cursor *cursor)
{
	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(vm, cursor, 1, true);
	new = duplicate_cursor(cursor, addr);
	add_cursor(&(vm->cursors), new);
	vm->cursors_num++;
	if (vm->log & OP_LOG)
		log_lfork(cursor, addr);
}
