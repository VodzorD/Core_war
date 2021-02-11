/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:30:49 by polina            #+#    #+#             */
/*   Updated: 2021/01/26 16:49:48 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*ft_find_label(char *name, t_asm *st)
{
	t_label	*tmp;

	name++;
	tmp = st->label;
	while(tmp && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (!tmp)
		error("Wrong label name ", st->string_num);
	return (tmp);
}

t_label	*ft_init_label(char *name, int bytes)
{
	t_label *new_label;

	if (!(new_label = malloc(sizeof(t_label))))
		error("Failed to allocate memory", 0);
	new_label->name = name;
	new_label->byte_pos = bytes;
	new_label->next = NULL;
	return (new_label);
}

void	ft_add_label(char *name, t_asm *st)
{
	t_label *tmp;
	
	if (!st->label)
		st->label = ft_init_label(name, st->count_bytes);
	else
	{
		tmp = st->label;
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, name))
				error("Same tag names ", st->string_num);
			tmp = tmp->next;
		}
		tmp->next = ft_init_label(name, st->count_bytes);
	}
}

char	*ft_create_name_label(char *colon, char **buf, t_asm *st)
{
	char	*name;
	char	*start;
	int		i;

	start = *buf;
	i = 0;
	while (*start && (*start == ' ' || *start == '\f' || *start == '\v' \
			|| *start == '\t' || *start == '\r'))
		start++;
	name = ft_strsub(start, 0, colon - start);
	while (name[i])
		if (!ft_strchr(LABEL_CHARS, name[i++]))
			error("Label names contains invalid charecters ", st->string_num);
	return (name);
}
