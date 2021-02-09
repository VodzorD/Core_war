# include "../../includes/corewar.h"

int32_t		bytecode_to_int32(const uint8_t *arena, int32_t addr, int32_t size)
{
	int32_t		result;
	int		sign;
	int			i;

	result = 0;
	sign = (arena[calc_addr(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((arena[calc_addr(addr + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += arena[calc_addr(addr + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void		int32_to_bytecode(uint8_t *arena, int32_t addr, int32_t value,
						int32_t size)
{
	int8_t i;

	i = 0;
	while (size)
	{
		arena[calc_addr(addr + size - 1)] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int32_t			crw_treg(t_cursor *cursor, int mode)
{
	(void)mode;
	return (cursor->reg[get_byte(cursor->vm, cursor ->offset + cursor->step) - 1]);
}

int32_t			crw_tdir(t_cursor *cursor, int mode)
{
	(void)mode;
	return (bytecode_to_int32(cursor->vm->arena,
							  cursor ->offset + cursor->step,
							  cursor->op->t_dir_size));
}

int32_t			crw_tind(t_cursor *cursor, int mode)
{
	int32_t		addr;

	addr = bytecode_to_int32(cursor->vm->arena,
							 cursor ->offset + cursor->step,
							 IND_SIZE);
	return (bytecode_to_int32(cursor->vm->arena,
							  cursor ->offset + (mode ? (addr % IDX_MOD) : addr),
							  DIR_SIZE));
}

int32_t		get_op_arg(t_cursor *cursor, uint8_t index, int mod)
{
	int32_t		value;

	value = 0;
	if (cursor->args_types[index] <= 4
			&& g_arg_hands[cursor->args_types[index]])
		value = g_arg_hands[cursor->args_types[index]](cursor, mod);
	cursor->step += step_size(cursor->args_types[index], cursor->op);
	return (value);
}

//void		update_map(t_vm *vm, t_cursor *cursor, int32_t addr, int32_t size)
//{
//	int32_t value;
//
//	value = ((cursor->player->id - 1) % 4) + 1;
//	while (size)
//	{
//		vm->vs->map[calc_addr(addr + size - 1)].index = value;
//		vm->vs->map[calc_addr(addr
//								+ size - 1)].wait_cycles_store = CYCLE_TO_WAIT;
//		size--;
//	}
//}
