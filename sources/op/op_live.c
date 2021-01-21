
# include "../../includes/corewar.h"
void				op_live(t_cursor *cursor)
{
	int32_t		player_id;
	t_player	*player;

	cursor->step += OP_CODE_LEN;
	player_id = get_op_arg(cursor, 0, 0) * -1;
	cursor->vm->lives_num++;
	cursor->last_live = cursor->vm->cycles;
	player = NULL;
//	(x >= 0 && ((unsigned int)x) == y)
	if (player_id > 0 && (size_t)player_id < cursor->vm->players.length)
	{
		player = lst_nth_data(&cursor->vm->players, player_id - 1);
		player->last_live = cursor->vm->cycles;
		player->current_lives_num++;
		cursor->vm->last_alive = player;
	}
}
