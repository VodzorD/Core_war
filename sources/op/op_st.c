void				op_st(t_vm *vm, t_cursor *cursor)
{
	int32_t	reg;
	int32_t	r_value;
	int32_t	addr;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = get_byte(vm, cursor->pc + cursor->step);
	r_value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
	if (cursor->args_types[1] == T_REG)
	{
		addr = get_byte(vm, cursor->pc + cursor->step);
		cursor->reg[addr - 1] = r_value;
		cursor->step += REG_LEN;
	}
	else
	{
		addr = bytecode_to_int32(vm->arena,
							cursor->pc + cursor->step, IND_SIZE);
		int32_to_bytecode(vm->arena, cursor->pc + (addr % IDX_MOD),
							r_value, DIR_SIZE);
		vs_st(vm, cursor, addr);
		cursor->step += IND_SIZE;
	}
	if (vm->log & OP_LOG)
		log_st(cursor->id, reg, addr);
}
