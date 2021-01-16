/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:09 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/14 18:00:08 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include <stdio.h>

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


t_vm		create_vm(void)
{
	t_vm	*vm;

	if (!(vm = ft_memalloc(sizeof(t_vm*))))
		ft_error("Alloc error", -1);
	return (vm)
}

int     main(int ac, char **av)
{
	t_vm	*vm;
	t_arg	*args;

	vm = create_vm();
	args = parse_options(ac, av, vm);
	vm = init_arena(args, vm);



    printf("%d\n", valid_flags(av, ac));
    return (0);
}