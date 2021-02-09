
# include "../../includes/corewar.h"
void	op_aff(t_cursor *cursor)
{
	int32_t	reg;
	int32_t	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	reg = get_byte(cursor->vm, cursor ->offset + cursor->step);
	value = cursor->reg[reg - 1];
	cursor->step += REG_LEN;
}
