/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:10 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/19 14:12:42 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H
# define ITERATOR_H

# include "../../core/includes/coreft.h"

typedef struct			s_iterator
{
	t_node				*cur_node;
	t_node				*start_node;
	ssize_t				len;
}						t_itr;

void					itr_reset(t_itr *itr);
void					itr_free(t_itr *itr);
void					itr_clear(t_itr *itr);
t_pntr					itr_next(t_itr *iterator);
int						itr_has_more(t_itr *itr);
void					itr_foreach(t_itr *iter, t_fmap for_func);


#endif
