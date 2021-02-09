
# include "../../includes/corewar.h"
void				op_lfork(t_cursor *cursor)
{
	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(cursor, 0, 1);
	new = clone_cursor(cursor);
	new->offset = calc_addr(addr + cursor->offset);
	qu_push_head(&cursor->vm->cursors, new);
//	ft_printf("create cursor %u, pl%u, offset%d\n", new->id, new->player->id, new->offset);
}
