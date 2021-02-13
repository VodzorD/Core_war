/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:20:51 by cshinoha          #+#    #+#             */
/*   Updated: 2021/02/12 22:56:46 by wscallop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coreft.h"

int					ft_atoi_check(int value, const char *str)
{
	char			*value_str;
	int				res;

	res = 0;
	value_str = ft_itoa_static(value);
	if (strcmp(value_str, str + (str[0] == '+')) == 0)
		res = 1;
	return (res);
}
