/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 23:16:49 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

t_node			*ft_node_prepend(t_node **begin_list, t_node *node)
{
	node->next = *begin_list;
	if (*begin_list)
		(*begin_list)->prev = node;
	node->prev = NULL;
	*begin_list = node;
	return (*begin_list);
}

t_node			*ft_data_prepend(t_node **begin_list, void *data)
{
	t_node		*first;

	if (!(first = ft_lstnew(data)))
		return (NULL);
	return (ft_node_prepend(begin_list, first));
}
