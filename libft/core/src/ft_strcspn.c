/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:54:50 by jpasty            #+#    #+#             */
/*   Updated: 2020/06/21 17:54:50 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strcspn(const char *str, const char *sym)
{
	const char	*s;
	const char	*c;

	s = str;
	while (*str)
	{
		c = sym;
		while (*c)
		{
			if (*str == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		str++;
	}
	return (str - s);
}
