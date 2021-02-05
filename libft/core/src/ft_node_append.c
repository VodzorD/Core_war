/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:29:22 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/02 14:57:07 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

t_node		*ft_node_append(t_node **node, t_node *new)
{
	t_node	*rover;
	if (*node)
	{
		rover = *node;
		while (rover->next)
			rover = rover->next;
		new->prev = rover;
		rover->next = new;
	}
	*node = new;
	return (new);
}


t_node		*ft_data_append(t_node **begin_list, t_pntr data)
{
	t_node	*new;

	if (!begin_list || !(new = ft_lstnew(data)))
		return (NULL);
	return (ft_node_append(begin_list, new));
}