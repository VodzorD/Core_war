
# include "../../includes/corewar.h"
void				op_lld(t_cursor *cursor)
{
	int32_t	value;
	int32_t	reg;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	value = get_op_arg(cursor, 0, 0);
	cursor->carry = (!value);
	reg = get_byte(cursor->vm, cursor ->offset + cursor->step);
	cursor->reg[reg - 1] = value;
	cursor->step += REG_LEN;
}
