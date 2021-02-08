
# include "../../includes/corewar.h"
void				op_zjmp(t_cursor *cursor)
{
	int32_t addr;
	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(cursor, 0, 1);
	if (cursor->carry)
	{
		cursor->offset = calc_addr(cursor->offset + (addr % IDX_MOD));
		cursor->step = 0;
	}
}
