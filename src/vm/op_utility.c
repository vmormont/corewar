/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:41:19 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/26 20:20:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool			isregister(char reg_num)
{
	if (reg_num > 1 && reg_num <= REG_NUMBER)
		return (TRUE);
	return (FALSE);
}

t_arg_type		get_arg_type(char code_args, char num_arg)
{
	if (num_arg == FIRST)
		return ((code_args >> 6) & 3);
	else if (num_arg == SECOND)
		return ((code_args >> 4) & 3);
	else if (num_arg == THIRD)
		return ((code_args >> 2) & 3);
	return (NONE);
}
