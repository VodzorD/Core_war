/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 23:13:43 by jpasty            #+#    #+#             */
/*   Updated: 2021/02/12 12:36:17 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		set_dump_flag(t_args *args, t_input *inp, t_opt *o)
{
	int			is_num;

	is_num = ft_is_number(o->optarg);
	if (!args->dump_print_mode && inp->ac > 1 && is_num &&
			((!o->optarg && ft_atoi(inp->av[2])) || o->optarg))
	{
		args->dump_cycle = o->optarg ? ft_atoi(o->optarg) :
							ft_atoi(*(inp->av + o->optind));
		if (args->dump_cycle < 0)
			args->dump_cycle = -1;
		if (!ft_strcmp(inp->av[1], "-d"))
			args->dump_print_mode = 64;
		else
			args->dump_print_mode = 32;
		o->optind = ft_is_number(inp->av[2]) ? 2 : 1;
		inp->av += o->optind;
		inp->ac -= o->optind;
	}
	else
		invalid_option(o);
}

static int		check_plr_number(t_args *args, t_input *inp, t_opt *o)
{
	int			plr_num;

	plr_num = ft_atoi(o->optarg);
	if (ft_is_number(o->optarg) && check_player_filename(
			inp->av[o->optind]) && plr_num < 9)
	{
		if (!args->players[plr_num - 1])
			args->players[plr_num - 1] = inp->av[o->optind];
		else
		{
			ft_printf("Player %s with the same number\n", inp->av[o->optind]);
			return (-1);
		}
	}
	else
		invalid_option(o);
	inp->av += o->optind;
	inp->ac -= o->optind;
	return ('n');
}

static void		check_remaining_args(t_input *inp, t_opt *o, t_qu *queue)
{
	if (*(inp->av + o->optind))
	{
		if (check_player_filename(inp->av[o->optind]))
			qu_push_head(queue, inp->av[o->optind]);
		else
			ft_error("Invalid champions file name", -1);
	}
	inp->av += o->optind;
	inp->ac -= o->optind;
}

void			fit_players(t_args *args, t_qu *qu)
{
	int			i;

	i = 0;
	while (i < args->count_players)
	{
		if (!args->players[i])
			args->players[i] = qu_pop_tail(qu);
		i++;
	}
	if (!qu_is_empty(qu))
		ft_error("Invalid number of players", -1);
}

void			parse_args(t_input inp, t_args *args)
{
	static t_qu	qu;
	static t_opt*o;
	int			rez;

	if ((args->count_players = count_plrs(inp.av)) > MAX_PLAYERS
		|| !args->count_players)
	{
		crw_usage();
		ft_error("Invalid number of players", -1);
	}
	while (inp.ac > 1)
	{
		rez = ft_getopt_long(inp, &o, set_lopt(), NULL);
		if (rez == '?')
			invalid_option(o);
		if (rez == 'd')
			set_dump_flag(args, &inp, o);
		if (rez == 'n')
			check_plr_number(args, &inp, o);
		if (rez == -1)
			check_remaining_args(&inp, o, &qu);
		o->optind = 1;
	}
	fit_players(args, &qu);
	free(o);
}
