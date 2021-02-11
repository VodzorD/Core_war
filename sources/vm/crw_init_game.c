#include "corewar.h"

static void 			init_arena(t_vm *vm)
{
	uint32_t	offset;
	t_itr		itr;
	t_player	*player;

	offset = 0;
	ft_bzero(&itr, sizeof(t_itr));
	lst_itr_load(&vm->players, &itr, NULL);
	while ((player = itr_next(&itr)))
	{
		ft_memcpy(&(vm->arena[offset]), player->code, player->code_size);
		offset += MEM_SIZE / vm->players.length;
	}
	itr_clear(&itr);
}

void	init_cursors(t_vm *vm)
{
	uint32_t	offset;
	t_itr		itr;
	static t_player	*player;
	static t_cursor *cursor;

	offset = 0;
	ft_bzero(&itr, sizeof(t_itr));
	lst_itr_load(&vm->players, &itr, NULL);
	while ((player = itr_next(&itr)))
	{
		cursor = create_cursor(player, offset, vm);
		qu_push_head(&vm->cursors, cursor);
		offset += MEM_SIZE / vm->players.length;
	}
	itr_clear(&itr);
}


t_vm					*crw_init_game(t_vm *vm)
{
	init_arena(vm);
	init_cursors(vm);
	return vm; //TODO
}