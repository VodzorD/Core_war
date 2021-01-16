/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_init_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:19:48 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/13 16:26:44 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// считывает игроков и создает лист игроков и добавляет айдишники если нет
static t_lst 			*parse_players(t_arg)
{
	return lst_new();
}

static t_vm 			*init_arena(t_vm *vm)
{
	uint32_t	offset;
	t_itr		itr;
	t_player	*player;

	offset = 0;
	itr = *lst_itr_load(vm->players, &itr, NULL);
	while ((player = itr_next(&itr)))
	{
		ft_memcpy(&(vm->arena[offset]), player->code, player->code_size);
		offset += MEM_SIZE / vm->players_num;
	}
}

void	init_cursors(t_vm *vm)
{
	uint32_t	offset;
	t_itr		*itr;
	t_player	*player;

	offset = 0;
	itr = lst_itr_load(vm->players, NULL, NULL);
	while ((player = itr_next(itr))
		   && lst_append(vm->cursors, create_cursor(player, offset))
		   && (offset += MEM_SIZE / vm->players_num)) {}
//	{
//		lst_append(vm->cursors, create_cursor(player, offset));
//		offset += MEM_SIZE / vm->players_num;
//	}
}

t_vm					*crw_init_game(t_vm *vm)
{
	return vm //TODO
}