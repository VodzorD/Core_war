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

t_args 		*parse_options(int ac, char **av, t_args *args)
{
//	char **tmp;
//	t_args *args;

//	int i = 0;
//	vm = ft_memalloc(sizeof(t_vm));
//	tmp = av;
//	while (*tmp)
//	{
//		if (ft_strstr(*tmp, ".cor") && ft_strcmp(*tmp, ".cor") != 0)
//			vm->players_num++;
//		tmp++;
//	}
	collect_args((t_input) {ac, av}, args);
//	while (i < args->count_players)

//	if (!queue)
//		printf("Empty queue");
//	while (i < vm->players_num)
//	{
//		if (vm->players[i])
//			printf("Plr num: %d, Plr name: %s\n",i + 1, vm->players[i]);
//		if (queue->next && !vm->players[i])
//		{
//			vm->players[i] = queue->content;
//			printf("Plr num: %d, Plr name: %s\n",i + 1, vm->players[i]);
//			queue = queue->next;
//		}
//		i++;
//	}
	return (args);
}