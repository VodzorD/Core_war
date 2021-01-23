/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crw_args_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:16:23 by cshinoha          #+#    #+#             */
/*   Updated: 2021/01/21 23:11:28 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO парсит флаги, инициализирует t_opt и возвращает
// t_arg с листо пар players { ид(если есть : имя файла чемпиона }

//t_arg 	parse_options(int ac, char **av, t_vm *vm)
//{
//	t_opt		opt = NULL;
//	t_arg		arg;
//	valid_flags(ac, av);
//	vm->opt = opt;
//	return arg;
//}

t_lst		parse_options(int ac, char **av, t_vm *vm)
{
	t_lst	args;
	t_pair	*pairs;
	t_opt
}