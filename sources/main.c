/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:09 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/19 20:30:35 by cshinoha         ###   ########.fr       */
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


t_vm		*create_vm(void)
{
	t_vm	*vm;

	if (!(vm = ft_memalloc(sizeof(t_vm*))))
		ft_error("Alloc error", -1);
	return (vm);
}

int     main(int ac, char **av)
{
	t_vm	*vm;
//	t_arg	*args;

	vm = create_vm();
    printf("%d\n", valid_flags(av, ac));
    return ((int)vm);
}