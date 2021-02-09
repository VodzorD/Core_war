/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartwith.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:11:19 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strstartwith(char *ref, char *stack)
{
	while (*ref)
	{
		if (*ref++ != *stack++)
			return (0);
	}
	return (1);
}