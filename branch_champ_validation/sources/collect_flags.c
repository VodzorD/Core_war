#include "corewar.h"

void				invalid_option(t_opt *opt)
{
	ft_printf("corewar: illegal option -- \'%s\'\n", opt->optopt);
	ft_printf("usage: ./corewar [-d nbr_cycles] [[-n number] champion1.co\n");
	ft_printf("or: [--dump nbr_cycles] ");
	free(opt);
	exit(2);
}

static void	set_dump_flag(t_vm *vm, t_input *inp, t_opt **o)
{
	int 	is_num;

	is_num = ft_is_only_digits((*o)->optarg);
	if (!vm->dump_print_mode && inp->ac > 1 && is_num &&
		(!(*o)->optarg && ft_atoi(*(inp->av + 2)) || (*o)->optarg))
	{
		vm->dump_cycle = (*o)->optarg ? ft_atoi((*o)->optarg) :
						 ft_atoi(*(inp->av + (*o)->optind));
		if (vm->dump_cycle  < 0)
			vm->dump_cycle = -1;
		if (!ft_strcmp(*(inp->av + 1), "-d"))
			vm->dump_print_mode = 64;
		else
			vm->dump_print_mode = 32;
		(*o)->optind =  ft_is_only_digits(*(inp->av + 2)) ? 2 : 1;
		inp->av += (*o)->optind;
		inp->ac -= (*o)->optind;
	}
	else
		invalid_option(*o);
}

static int check_plr_number(t_vm *vm, t_input *inp, t_opt **o)
{
	int		plr_num;

	plr_num = ft_atoi((*o)->optarg);
	if (ft_is_only_digits((*o)->optarg) && check_player_filename(
			*(inp->av + (*o)->optind)) && plr_num < 9)
	{
		if (!vm->players[plr_num - 1])
			vm->players[plr_num -1] = create_plr(*(inp->av + (*o)->optind));
		else
		{
			ft_printf("Player %s with the same number\n",
			 						*(inp->av + (*o)->optind));
			return (-1);
		}
	}
	else
		invalid_option(*o);
	inp->av += (*o)->optind;
	inp->ac -= (*o)->optind;
	return ('n');
}

static void check_remaining_args(t_input *inp, t_opt **o, t_qu **queue)
{
	if (*(inp->av + (*o)->optind))
	{
		if (check_player_filename(*(inp->av + (*o)->optind)))
			qu_push_head(*queue, *(inp->av + (*o)->optind));
		else
			ft_printf("Player %s don't play this game\n",
			 						*(inp->av + (*o)->optind));
	}
	inp->av += (*o)->optind;
	inp->ac -= (*o)->optind;
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

int8_t 		check_player_filename(char *filename)
{
	char	*ext;

	ext = ft_strchr(filename, '.');
	if (*filename != '.' && ext)
		if (ft_strcmp(ext, ".cor"))
			return (1);
	return (0);
}

t_lst		*collect_args(t_vm **vm, t_input inp, t_qu *queue)
{
	t_opt	*o;
	int 	rez;

	o = NULL;
	while (inp.ac > 1)
	{
		rez = ft_getopt_long(inp, &o, set_lopt(), NULL);
		if (rez == '?')
			invalid_option(o);
		if (rez == 'd')
			set_dump_flag(*vm, &inp, &o);
		if (rez == 'n')
			check_plr_number(*vm, &inp, &o);
		if (rez == -1)
			check_remaining_args(&inp, &o, &queue);
		o->optind = 1;
	}
	free(o);
	//TODO вернуть список с игроками в правильном порядке
	return (create_lst);
}