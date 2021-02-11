/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itr_foreach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:15:21 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/11 18:15:40 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/includes/coreft.h"
#include <iterator.h>

void			itr_foreach(t_itr *itr, t_fmap for_func)
{
	ft_lstiter(itr->cur_node, (void (*)(t_pntr *)) for_func);
}
