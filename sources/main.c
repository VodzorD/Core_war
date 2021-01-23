/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:09 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/21 18:17:56 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

t_lst		*read_prog_args(int ac, char **av)
{
	t_lst	*corewar_args;
	t_pair	*pair;

	return (corewar_args);
}

int32_t		calc_addr(int32_t addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

inline int8_t	get_byte(t_vm *vm, int32_t addr)
{
	return (vm->arena[addr % MEM_SIZE]);
}

static int      valid_flags(char **av, int ac)
{
    int     i;

    i = 0;
    while (i < ac)
    {
        if (av[i][0] == '-')
            if (!ft_strcmp(av[i], "-n") || !ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-d"))
                return (1);
        i++;
    }
    return (0);
}


t_vm		*create_vm(void)
{
	t_vm	*vm;

	if (!(vm = ft_memalloc(sizeof(t_vm))))
		ft_error("Alloc error", -1);
	vm->cycles_to_die = CYCLE_TO_DIE;
	return (vm);
}

int     main(int ac, char **av)
{
	t_vm	*vm;
	t_lst	*corewar_args;

	printf("%d\n", valid_flags(av, ac));
	corewar_args = read_prog_args(ac, av);
	vm = create_vm();
    vm->players = champs_validation(corewar_args);

    crw_init_game(vm);
	crw_exec(vm);
}