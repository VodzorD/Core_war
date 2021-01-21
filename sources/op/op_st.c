
# include "../../includes/corewar.h"
void				op_st(t_cursor *cursor)
{
	int32_t	reg;
	int32_t	r_value;
	int32_t	addr;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = get_byte(cursor->vm, cursor ->offset + cursor->step);
	r_value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
	if (cursor->args_types[1] == T_REG)
	{
		addr = get_byte(cursor->vm, cursor ->offset + cursor->step);
		cursor->reg[addr - 1] = r_value;
		cursor->step += REG_LEN;
	}
	else
	{
		addr = bytecode_to_int32(cursor->vm->arena,
							cursor ->offset + cursor->step, IND_SIZE);
		int32_to_bytecode(cursor->vm->arena, cursor ->offset + (addr % IDX_MOD),
							r_value, DIR_SIZE);
		cursor->step += IND_SIZE;
	}
}
