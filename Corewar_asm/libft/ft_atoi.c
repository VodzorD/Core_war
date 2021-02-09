/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:38:31 by vheidy            #+#    #+#             */
/*   Updated: 2021/01/20 17:59:12 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long int		result;
	int				neg;

	result = 0;
	neg = 1;
	while (*str == 32 || *str == '\t' || *str == '\n' ||
				*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		str++;
		neg = -1;
	}
	if (*str == '+' && neg == 1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	if (result > result * 10)
		return (-(neg == 1));
	return (result * neg);
}
