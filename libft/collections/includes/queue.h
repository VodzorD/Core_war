/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:24 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/21 23:11:17 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "../../core/includes/coreft.h"
# include "list.h"
//TODO replace by t_node

typedef struct				s_queue
{
	t_node					*head;
	t_node					*tail;
	size_t					len;
}							t_qu;

//typedef struct		s_node
//{
//	void			*data;
//	struct s_node	*next;
//	struct s_node	*prev;
//}					t_node;

t_pntr			qu_rm_data(t_qu *qu, t_fequal equal, t_pntr data);
void			qu_foreach(t_qu *qu, t_fmap foreach);
t_itr			*qu_itr_load(t_qu *qu, t_itr *itr, t_fprdct prdct);
t_qu						*qu_by_lst(t_lst *lst);
int							qu_contains(t_qu *qu, t_pntr data);
t_qu						*qu_new(void);
void						qu_free(t_qu *queue);
void						qu_clear(t_qu *queue);
int							qu_push_head(t_qu *queue, t_pntr data);
t_pntr						qu_pop_head(t_qu *queue);
t_pntr						qu_peek_head(t_qu *queue);
int							qu_push_tail(t_qu *queue, t_pntr data);
t_pntr						qu_pop_tail(t_qu *queue);
t_pntr						qu_peek_tail(t_qu *queue);
int							qu_is_empty(t_qu *queue);

#endif
