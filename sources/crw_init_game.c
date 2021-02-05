/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_init_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:19:48 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/22 19:46:40 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int32_t	parse_int32(int fd)
{
//	ssize_t	size;
	uint8_t	buffer[4];

	read(fd, &buffer, 4);
//	if (size == -1)
//		terminate(ERR_READ_FILE);
//	if (size < 4)
//		terminate(ERR_INVALID_FILE);
	return (bytecode_to_int32(buffer, 0, 4));
}

static char		*parse_str(int fd, size_t len)
{
	char	*buffer;

	buffer = ft_strnew(len);
	read(fd, buffer, len);
	return (buffer);
}

static uint8_t	*parse_code(int fd, size_t len)
{
	uint8_t	*buffer;

	buffer = malloc(len);
	read(fd, buffer, len);
	return (buffer);
}

t_player		*parse_champion(char *filename, int id)
{
	t_player	*player;
	int			fd;

	player = create_player(id);
	fd = open(filename, O_RDONLY);
	parse_int32(fd);
	player->name = parse_str(fd, PROG_NAME_LENGTH);
	parse_int32(fd);
	player->code_size = parse_int32(fd);
	player->comment = parse_str(fd, COMMENT_LENGTH);
	parse_int32(fd);
	player->code = parse_code(fd, (size_t)player->code_size);
	return (player);
}

// считывает игроков и создает лист игроков и добавляет айдишники если нет
//static t_lst 			*parse_players(t_arg)
//{
//	return lst_new();
//}

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
}

t_pair					*create_pair(t_pntr left, t_pntr right)
{
	t_pair				*pair;

	pair = malloc(sizeof(t_pair));
	pair->key = left;
	pair->value = right;
	return (pair);
}


t_vm					*crw_init_game(t_vm *vm)
{


	lst_append(&vm->arg.players, create_pair((t_pntr) 2, ft_strdup("second.cor")));
	lst_append(&vm->arg.players, create_pair((t_pntr) 1, ft_strdup("first.cor")));
	champ_validation(&vm->arg.players, &vm->players);
	init_arena(vm);
	init_cursors(vm);

//	pair = ft_memalloc(sizeof(t_pair));
//	pair->key = (t_pntr) 1;
//	ft_strcpy(pair->value, "first.cor");
//	lst_append(pairs, pair);
//	pair->key = (t_pntr) 2;
//	ft_strcpy(pair->value, "second.cor");
//	lst_append(pairs, pair);

	return vm; //TODO
}