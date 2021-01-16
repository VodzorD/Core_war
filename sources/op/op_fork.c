void				op_fork(t_vm *vm, t_cursor *cursor)
{
	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(vm, cursor, 1, true);
	new = duplicate_cursor(cursor, addr % IDX_MOD);
	add_cursor(&(vm->cursors), new);
	vm->cursors_num++;
	if (vm->log & OP_LOG)
		log_fork(cursor, addr);
}
