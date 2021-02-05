/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_args_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:16:23 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/03 20:57:55 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO парсит флаги, инициализирует t_opt и возвращает
// t_arg с листо пар players { ид(если есть : имя файла чемпиона }

//t_arg 	parse_options(int ac, char **av, t_vm *vm)
//{
//	t_opt		opt = NULL;
//	t_arg		arg;
//	valid_flags(ac, av);
//	vm->opt = opt;
//	return arg;
//}

int32_t		count_plrs(char **av)
{
	int32_t	plrs_num;

	plrs_num = 0;
	while (*av)
	{
		if (ft_strstr(*av, ".cor") && !ft_strcmp(*av, ".cor"))
			plrs_num++;
		*av++;
	}
	return (plrs_num);
}

t_lst		*parse_options(int ac, char **av, t_vm *vm)
{
	char **tmp;
	t_qu *queue;
	int i = 0;

	queue = qu_new();
	vm = ft_memalloc(sizeof(t_vm));
	tmp = av;
	while (*tmp)
	{
		if (ft_strstr(*tmp, ".cor") && ft_strcmp(*tmp, ".cor") != 0)
			vm->players_num++;
		tmp++;
	}
	if (vm->players_num > MAX_PLAYERS)
		exit(EXIT_FAILURE);
	queue = collect_flags(&vm, (t_input ) {ac, av});
	if (!queue)
		printf("Empty queue");
	while (i < vm->players_num)
	{
		if (vm->players[i])
			printf("Plr num: %d, Plr name: %s\n",i + 1, vm->players[i]);
		if (queue->next && !vm->players[i])
		{
			vm->players[i] = queue->content;
			printf("Plr num: %d, Plr name: %s\n",i + 1, vm->players[i]);
			queue = queue->next;
		}
		i++;
	}
	return args;
}