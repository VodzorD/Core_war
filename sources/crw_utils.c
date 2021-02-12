/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:01:35 by jpasty            #+#    #+#             */
/*   Updated: 2021/02/12 12:33:34 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline int32_t		calc_addr(int32_t addr)
{
	return ((addr %= MEM_SIZE) < 0 ? addr + MEM_SIZE : addr);
}

inline int8_t		get_byte(t_vm *vm, int32_t addr)
{
	return (vm->arena[calc_addr(addr)]);
}

void				crw_usage(void)
{
	ft_printf("usage: ./corewar [-d nbr_cycles] [[-n number]\n"
			"or: ./corewar [--dump nbr_cycles] [--number number]\n"
			"max players: %u\n", MAX_PLAYERS);
}

void				invalid_option(t_opt *opt)
{
	ft_printf("corewar: invalid option -- \'%sv\'\n",
			opt->optopt ? opt->optopt : opt->optarg);
	crw_usage();
	free(opt);
	exit(2);
}

t_lopt				*set_lopt(void)
{
	static t_lopt	lopt[] = {
			{"dump", REQ_ARG, NULL, 'd'},
			{"number", REQ_ARG, NULL, 'n'},
			{NULL, 0, NULL, 0}
	};

	return (lopt);
}
