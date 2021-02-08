# include "../includes/corewar.h"

t_player	*create_player(int id)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		ft_error("ERR_PLAYER_INIT", -1);
	player->id = id;
	return (player);
}