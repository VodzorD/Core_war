#include "../includes/corewar.h"

t_vm		*create_vm(t_vm *vm)
{
	vm->cycles_to_die = CYCLE_TO_DIE;
	return (vm);
}

int     main(int ac, char **av)
{
	static t_vm	vm;

	create_vm(&vm);
	parse_options(--ac, ++av, &vm.arg);
	champ_validation(&vm.arg, &vm.players);
    crw_init_game(&vm);
	crw_exec(&vm);
}