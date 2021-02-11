/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:07:06 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/22 19:03:29 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_qu			*qu_new(void)
{
	t_qu		*qu;

	if (!(qu = (t_qu *)malloc(sizeof(t_qu))))
		return (NULL);
	qu->head = NULL;
	qu->tail = NULL;
	qu->len = 0;
	return (qu);
}

t_qu			*qu_by_lst(t_lst *lst)
{
	t_qu		*qu;
	t_node		*node;
	size_t		i;

	if (!(qu = qu_new()))
		return (NULL);
	node = lst->first;
	i = 0;
	while (i++ < lst->length)
	{
		if (!(qu_push_head(qu, node->data)))
			return (NULL);
		node = node->next;
	}
	return (qu);
}

void			qu_free(t_qu *qu)
{
	qu_clear(qu);
	free(qu);
}

void			qu_clear(t_qu *qu)
{
	while (!qu_is_empty(qu))
		qu_pop_head(qu);
}

int				qu_contains(t_qu *qu, t_pntr data)
{
	t_node	*entry;

	entry = qu->head;
	while (entry)
	{
		if (entry->data == data)
			return (1);
		entry = entry->next;
	}
	return (0);
}
