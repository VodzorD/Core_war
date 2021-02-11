/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:02:10 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 19:09:15 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int32_t			crw_treg(t_cursor *cursor, int mode)
{
	(void)mode;
	return (cursor->reg[get_byte(cursor->vm,
							cursor->offset + cursor->step) - 1]);
}

int32_t			crw_tdir(t_cursor *cursor, int mode)
{
	(void)mode;
	return (bytecode_to_int32(cursor->vm->arena,
				cursor->offset + cursor->step,
						cursor->op->t_dir_size));
}

int32_t			crw_tind(t_cursor *cursor, int mode)
{
	int32_t		addr;

	addr = bytecode_to_int32(cursor->vm->arena,
						cursor->offset + cursor->step,
								IND_SIZE);
	return (bytecode_to_int32(cursor->vm->arena,
							cursor->offset + (mode ? (addr % IDX_MOD) : addr),
									DIR_SIZE));
}
