#include "corewar.h"

void				invalid_option(t_opt *opt)
{
	ft_printf("corewar: illegal option -- \'%s\'\n", opt->optopt);
	ft_printf("usage: ./corewar [-d nbr_cycles] [[-n number] champion1.co\n");
	ft_printf("or: [--dump nbr_cycles] ");
	free(opt);
	exit(2);
}
static int8_t	set_dump_flag(t_vm *vm, t_input *inp, t_opt **o)
{
	if (!vm->dump_print_mode && inp->ac >= 2)
	{
		if ((vm->dump_cycle = ft_atoi(*(inp->av + 1)) < 0))
			vm->dump_cycle = -1;
		if (!ft_strcmp(*(inp->av + 1), "-d"))
			vm->dump_print_mode = 64;
		else
			vm->dump_print_mode = 32;
		inp->av += (*o)->optind;
		inp->ac -= (*o)->optind;
		(*o)->optind = 1;
	}
	else
		invalid_option(*o);
}

void				set_flag(int rez, t_flag *flag)
{
	if (rez == 'd')
		flag->d = 1;
	else if (rez == 'n')
		flag->n = 1;
}

t_lopt				*set_lopt(void)
{

	static t_lopt	lopt[] = {
			{"dump", REQ_ARG, NULL, 'd'},
			{NULL, 0, NULL, 0}
	};
	return (lopt);
}

int8_t 		check_player_filename(char *filename)
{
	char	*ext;

	ext = ft_strchr(filename, '.');
	if (*filename != '.' && ext)
		if (ft_strcmp(ext, ".cor"))
			return (1);
	return (0);
}

void		collect_args(t_vm **vm, t_input inp, t_qu **queue)
{
	t_opt	*o;
	int 	rez;

	o = NULL;
	while (inp.ac > 1)
	{
		rez = ft_getopt_long(inp, &o, set_lopt(), NULL);
		if (rez == '?')
			invalid_option(o);
		if (rez == 'n')
		{
			if (check_player_filename(*(inp.av + o->optind)))
				if (ft_atoi(o->optarg) > 0 && ft_atoi(o->optarg) != MAX_PLAYERS)
					lst_append(&(*vm)->players, *(inp.av + o->optind));
			o->optind = 1;
		}
		if (rez == 'd')
			set_dump_flag(*vm, &inp, &o);
		if (rez == -1)
			if (*(inp.av + o->optind))
				if (check_player_filename(*(inp.av + o->optind)))
					qu_push_head(*queue, *(inp.av + o->optind));
		inp.av += o->optind;
		inp.ac -= o->optind;
	}
	free(o);
}