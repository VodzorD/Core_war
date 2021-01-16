void				op_xor(t_vm *vm, t_cursor *cursor)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	reg;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	value_1 = get_op_arg(vm, cursor, 1, true);
	value_2 = get_op_arg(vm, cursor, 2, true);
	value = value_1 ^ value_2;
	cursor->carry = !value;
	reg = get_byte(vm, cursor->pc + cursor->step);
	cursor->reg[reg - 1] = value;
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_xor(cursor->id, value_1, value_2, reg);
}
