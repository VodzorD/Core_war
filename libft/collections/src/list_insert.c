/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:06:42 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/02 14:57:07 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_node				*lst_prepend(t_lst *lst, t_pntr data)
{
	t_node			*new;

	if (!lst || !(new = ft_data_prepend(&lst->first, data)))
		return (NULL);
	if (!lst->length)
	{
		lst->last = new;
		lst->first = new;
	}
	lst->length++;
	return (new);
}

t_node				*lst_append(t_lst *lst, t_pntr data)
{
	t_node			*new;

	if (!lst || !(new = ft_data_append(&lst->last, data)))
		return (NULL);
	if (!lst->length)
	{
		lst->last = new;
		lst->first = new;
	}
	lst->length++;
	return (new);
}
