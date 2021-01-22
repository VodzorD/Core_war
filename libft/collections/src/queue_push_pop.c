/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:53:41 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/22 19:03:16 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

int				qu_push_tail(t_qu *qu, t_pntr data)
{
	t_node			*new;

	if (!qu || !(new = ft_node_append(&qu->head, data)))
		return (0);
	if (!qu->len)
	{
		qu->tail = new;
		qu->head = new;
	}
	qu->len++;
	return (1);
}

t_pntr			qu_pop_tail(t_qu *qu)
{
	t_node		*entry;
	t_pntr		result;

	if (qu_is_empty(qu))
		return (NULL);
	entry = qu->tail;
	qu->tail = entry->prev;
	result = entry->data;
	if (!qu->tail)
		qu->head = NULL;
	else
		qu->tail->next = NULL;
	free(entry);
	qu->len--;
	return (result);
}

int				qu_push_head(t_qu *qu, t_pntr data)
{
	if (!qu || !(ft_node_prepend(&qu->head, data)))
		return (0);
	if (!qu->len)
		qu->tail = qu->head;
	qu->len++;
	return (1);
}

t_pntr			qu_pop_head(t_qu *qu)
{
	t_node		*entry;
	t_pntr		result;

	if (qu_is_empty(qu))
		return (NULL);
	entry = qu->head;
	qu->head = entry->next;
	result = entry->data;
	if (!qu->head)
		qu->tail = NULL;
	else
		qu->head->prev = NULL;
	free(entry);
	qu->len--;
	return (result);
}

t_pntr			qu_rm_data(t_qu *qu, t_fequal equal, t_pntr data)
{
	t_node		*node;

	node = qu->head;
	while (node)
	{
		if ((!equal && data == node->data)
			|| (equal && equal(node->data, data)))
		{
			node = ft_node_del(node, NULL);
			if (node == qu->head)
				qu->head = qu->head->next;
			if (node == qu->tail)
				qu->tail = qu->tail->prev;
			qu->len--;
			node->prev = NULL;
			node->next = NULL;
			free(node);
			return (data);
		}
		node = node->next;
	}
	return (NULL);
}
