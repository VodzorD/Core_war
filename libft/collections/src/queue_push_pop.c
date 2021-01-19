/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:53:41 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/16 20:44:56 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

int				qu_push_tail(t_qu *qu, t_pntr data)
{
	t_node			*new;

	if (!qu || !(new = ft_node_prepend(&qu->head, data)))
		return (0);
	if (!qu->len)
	{
		qu->tail = new;
		qu->head = new;
	}
	qu->len++;
	return (1);

//	t_node		*new_entry;
//
//	if (!(new_entry = malloc(sizeof(t_node))))
//		return (0);
//	new_entry->data = data;
//	new_entry->prev = qu->tail;
//	new_entry->next = NULL;
//	if (!qu->tail)
//	{
//		qu->head = new_entry;
//		qu->tail = new_entry;
//	}
//	else
//	{
//		qu->tail->next = new_entry;
//		qu->tail = new_entry;
//	}
//	qu->len++;
//	return (1);
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
	t_node			*new;

	if (!qu || !(new = ft_node_append(&qu->head, data)))
		return (0);
	if (!qu->len)
	{
		qu->head = new;
		qu->tail = new;
	}
	qu->len++;
	return (1);

//	t_qu_entry	*node;
//
//	if (!qu || !(node = malloc(sizeof(t_qu_entry))))
//		return (0);
//	node->data = data;
//	node->prev = NULL;
//	node->next = qu->head;
//	if (!qu->head)
//	{
//		qu->head = node;
//		qu->tail = node;
//	}
//	else
//	{
//		qu->head->prev = node;
//		qu->head = node;
//	}
//	qu->len++;
//	return (1);
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

t_pntr data		qu_rm_data(t_qu *qu, t_fequal equal, t_pntr data)
{
	t_node		*node;

	node = qu->head;
	while (node)
	{
		if ((!equal && data == node-data)
			|| (equal && equal(node->data, data)))
		{
			node = ft_node_del(node, NULL);
			if (node == qu->head)
				qu->head = qu->head->next;
			if (node == qu->tail)
				qu->tail = qu->tail->prev;
			qu->length--;
			node->prev = NULL;
			node->next = NULL;
			free(node);
			return (data);
		}
		node = node->next;
	}
	return (NULL);
}
