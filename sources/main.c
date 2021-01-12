/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:39:09 by wscallop          #+#    #+#             */
/*   Updated: 2021/01/12 15:54:09 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

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

int     main(int ac, char **av)
{
    printf("%d\n", valid_flags(av, ac));
    return (0);
}