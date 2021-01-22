/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_peek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:55:11 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_pntr			qu_peek_head(t_qu *qu)
{
	return (!qu_is_empty(qu) ? qu->head->data : NULL);
}

t_pntr			qu_peek_tail(t_qu *qu)
{
	if (qu_is_empty(qu))
		return (NULL);
	return (qu->tail->data);
}

int				qu_is_empty(t_qu *qu)
{
	return (!qu->head);
}

void			qu_foreach(t_qu *qu, t_fmap foreach)
{
	ft_lstiter(qu->head, (void (*)(t_pntr *)) foreach);
}


t_itr			*qu_itr_load(t_qu *qu, t_itr *itr, t_fprdct prdct)
{
	size_t		i;
	t_node 		*entry;

	itr_clear(itr);
	if (!itr && !(itr = ft_memalloc(sizeof(t_itr))))
		return (NULL);
	entry = qu->tail;
	i = 0;
	while (i++ < qu->len)
	{
		if (!prdct || prdct(entry->data))
		{
			ft_node_prepend(&itr->cur_node, entry->data);
			itr->len++;
		}
		entry = entry->prev;
	}
	itr->start_node = itr->cur_node;
	return (itr);
}