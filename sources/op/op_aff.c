void	op_aff(t_vm *vm, t_cursor *cursor)
{
	int32_t	reg;
	int32_t	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = get_byte(vm, cursor->pc + cursor->step);
	value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
	if (vm->display_aff)
		ft_printf("Aff: %c\n", (char)value);
	if (vm->vs)
	{
		vm->vs->aff_symbol = (char)value;
		vm->vs->aff_player = cursor->player;
	}
}
