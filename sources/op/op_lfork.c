
# include "../../includes/corewar.h"
void				op_lfork(t_cursor *cursor)
{
	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(cursor, 0, 1);
	new = clone_cursor(cursor);
	new->offset = addr % MEM_SIZE;
	qu_push_head(&cursor->vm->cursors, new);
}
