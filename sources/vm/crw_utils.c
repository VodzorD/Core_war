/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:15:44 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:16:17 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline int32_t	calc_addr(int32_t addr)
{
	return ((addr %= MEM_SIZE) < 0 ? addr + MEM_SIZE : addr);
}

inline int8_t	get_byte(t_vm *vm, int32_t addr)
{
	return (vm->arena[calc_addr(addr)]);
}

void			invalid_option(t_opt *opt)
{
	ft_printf("corewar: illegal option -- \'%s\'\n", opt->optopt);
	ft_printf("usage: ./corewar [-d nbr_cycles] [[-n number] champion1.co\n");
	ft_printf("or: [--dump nbr_cycles] ");
	free(opt);
	exit(2);
}
