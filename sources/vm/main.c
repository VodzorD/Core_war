/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:39:04 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:39:18 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_vm		*create_vm(t_vm *vm)
{
	vm->cycles_to_die = CYCLE_TO_DIE;
	return (vm);
}

int			main(int ac, char **av)
{
	static t_vm	vm;

	create_vm(&vm);
	parse_args((t_input){--ac, ++av}, &vm.arg);
	champ_validation(&vm.arg, &vm.players);
	crw_init_game(&vm);
	crw_exec(&vm);
	lst_clear(&vm.players, (t_ffree) & dstr_player);
	qu_clear(&vm.cursors);
}
