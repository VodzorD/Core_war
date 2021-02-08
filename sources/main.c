#include "../includes/corewar.h"
#include <stdio.h>

inline int32_t		calc_addr(int32_t addr)
{
	return  ((addr %= MEM_SIZE) < 0 ? addr + MEM_SIZE : addr);
}

inline int8_t	get_byte(t_vm *vm, int32_t addr)
{
	return (vm->arena[calc_addr(addr)]);
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

	vm = create_vm();
    printf("%d\n", valid_flags(av, ac));
    crw_init_game(vm);
	crw_exec(vm);
}