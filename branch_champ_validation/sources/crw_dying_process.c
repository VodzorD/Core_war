/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_dying_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:36:52 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/20 19:36:19 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/corewar.h"

static int	is_died(t_cursor *cursor)
{
	return (cursor->vm->cycles_to_die <= 0
			|| cursor->vm->cycles - cursor->last_live
			   >= cursor->vm->cycles_to_die);
}

static void		delete_died_cursors(t_vm *vm)
{
	t_itr		itr;

	ft_bzero(&itr, sizeof(t_itr));
	qu_itr_load(&vm->cursors, &itr, (t_fprdct)&is_died);
	while (itr_has_more(&itr))
		free(qu_rm_data(&vm->cursors, NULL, itr_next(&itr))); //TODO
	itr_clear(&itr);
}

static void		reset_live(t_player *pl)
{
	pl->current_lives_num = 0;
}

void			cycles_to_die_check(t_vm *vm)
{
	vm->checks_num++;
	delete_died_cursors(vm);
	if (vm->lives_num >= NBR_LIVE
		|| vm->checks_num == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks_num = 0;
	}
	lst_foreach(&vm->players, (t_fmap)&reset_live);
	vm->cycles_after_check = 0;
}