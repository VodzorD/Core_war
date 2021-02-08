
# include "../../includes/corewar.h"
void				op_fork(t_cursor *cursor)
{
//	int32_t		addr;
	t_cursor	*new;

	cursor->step += OP_CODE_LEN;
//	addr = get_op_arg(cursor, 0, 1);
	new = clone_cursor(cursor);
	new->offset = calc_addr(cursor->offset + get_op_arg(cursor, 0, 1) % IDX_MOD);
	qu_push_head(&cursor->vm->cursors, new);
//	ft_printf("create cursor %u, pl%u, offset%u\n", new->id, new->player->id, new->offset);
}
