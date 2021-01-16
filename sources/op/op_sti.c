void				op_sti(t_vm *vm, t_cursor *cursor)
{
	int32_t	reg;
	int32_t	value;
	int32_t	addr_1;
	int32_t	addr_2;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	reg = get_byte(vm, cursor->pc + cursor->step);
	value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
	addr_1 = get_op_arg(vm, cursor, 2, true);
	addr_2 = get_op_arg(vm, cursor, 3, true);
	int32_to_bytecode(vm->arena,
			(cursor->pc + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
	if (vm->vs)
		update_map(vm, cursor, cursor->pc + ((addr_1 + addr_2) % IDX_MOD),
																DIR_SIZE);
	if (vm->log & OP_LOG)
		log_sti(cursor, reg, addr_1, addr_2);
}
