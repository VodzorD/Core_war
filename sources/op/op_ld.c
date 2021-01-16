void				op_ld(t_vm *vm, t_cursor *cursor)
{
	int32_t	value;
	int32_t	reg;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	value = get_op_arg(vm, cursor, 1, true);
	cursor->carry = (t_bool)(!value);
	reg = get_byte(vm, cursor->pc + cursor->step);
	cursor->reg[reg - 1] = value;
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_ld(cursor->id, value, reg);
}
