#include "corewar.h"

static void	set_dump_flag(t_args *args, t_input *inp, t_opt *o)
{
	int 	is_num;

	is_num = ft_is_number(o->optarg);
	if (!args->dump_print_mode && inp->ac > 1 && is_num &&
        (!o->optarg && ft_atoi(inp->av[2]) || o->optarg)) //TODO '&&' within '||' [-Wlogical-op-parentheses]
	{
        args->dump_cycle = o->optarg ? ft_atoi(o->optarg) :
                           ft_atoi(*(inp->av + o->optind));
		if (args->dump_cycle < 0)
            args->dump_cycle = -1;
		if (!ft_strcmp(inp->av[1], "-d"))
            args->dump_print_mode = 64;
		else
            args->dump_print_mode = 32;
		o->optind =  ft_is_number(inp->av[2]) ? 2 : 1;
		inp->av += o->optind;
		inp->ac -= o->optind;
	}
	else
		invalid_option(o);
}

static int check_plr_number(t_args *args, t_input *inp, t_opt *o)
{
	int		plr_num;

	plr_num = ft_atoi(o->optarg);
	if (ft_is_number(o->optarg) && check_player_filename(
			inp->av[o->optind]) && plr_num < 9)
	{
		if (!args->players[plr_num - 1])
			args->players[plr_num -1] = inp->av[o->optind];
		else
		{
			ft_printf("Player %s with the same number\n",
			 						inp->av[o->optind]);
			return (-1);
		}
	}
	else
		invalid_option(o);
	inp->av += o->optind;
	inp->ac -= o->optind;
	return ('n');
}

static void check_remaining_args(t_input *inp, t_opt *o, t_qu *queue)
{
	if (*(inp->av + o->optind))
	{
		if (check_player_filename(inp->av[o->optind]))
			qu_push_head(queue, inp->av[o->optind]);
		else
			ft_printf("Player %s don't play this game\n",
			 						inp->av[o->optind]);
	}
	inp->av += o->optind;
	inp->ac -= o->optind;
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
		if (!ft_strcmp(ext, ".cor"))
			return (1);
	return (0);
}

int32_t		count_plrs(char **av)
{
	int32_t	plrs_num;

	plrs_num = 0;
	while (*av)
	{
		if (ft_strendwith(".cor", *av)) //TODO create str_end0_with()
			plrs_num++;
		*av++;
	}
	return (plrs_num);
}

void		fit_players(t_args *args, t_qu *qu) {
	int		i;

	i = 0;
	while (i < args->count_players)
	{
		if (!args->players[i])
			args->players[i] = qu_pop_tail(qu);
		i++;
	}
	if (!qu_is_empty(qu))
		ft_error("Ошибочка", -1);
}

t_args 		*collect_args(t_input inp, t_args *args)
{
	static t_opt	o;
	int 	rez;
	static  t_qu qu;

	if ((args->count_players = count_plrs(inp.av)) > MAX_PLAYERS)
		ft_error("Ошибочка", -1);
	while (inp.ac > 1)
	{
		rez = ft_getopt_long(inp, &o, set_lopt(), NULL);
		if (rez == '?')
			invalid_option(&o);
		if (rez == 'd')
			set_dump_flag(args, &inp, &o);
		if (rez == 'n')
			check_plr_number(args, &inp, &o);
		if (rez == -1)
			check_remaining_args(&inp, &o, &qu);
		o.optind = 1;
	}
	fit_players(args, &qu);
	return (args);
}