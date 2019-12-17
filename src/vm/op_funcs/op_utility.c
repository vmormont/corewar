/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:41:19 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/17 23:28:10 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

int			get_arg_size(char op_code, t_arg_type type)
{
	if (type == REG_CODE)
		return (ARENA_REG_SIZE);
	else if (type == DIR_CODE)
		return (g_op_tab[op_code].tdir_size);
	else if (type == IND_CODE)
		return (IND_SIZE);
	return (0);
}

int			get_arg_value(char *arena, t_cursor *cursor, t_arg_type type)
{
	short		address;
	int			value;

	value = 0;
	if (type == REG_CODE)
		value = cursor->reg[arena[(cursor->pos + cursor->step) % MEM_SIZE]];
	else if (type == DIR_CODE)
	{
		value = read_to_int(arena, cursor->pos + cursor->step,\
		g_op_tab[cursor->op_code].tdir_size);
	}
	else if (type == IND_CODE)
	{
		address = read_to_int(arena, cursor->pos + cursor->step, IND_SIZE);
		if (cursor->op_code != LLD && cursor->op_code != LLDI)
			address = address % IDX_MOD;
		value = read_to_int(arena, cursor->pos + address, DIR_SIZE);
	}
	cursor->step += get_arg_size(cursor->op_code, type);
	return (value);
}
