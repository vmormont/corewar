/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:41:19 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/14 11:10:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

t_bool		isregister(char reg_num)
{
	if (reg_num > 0 && reg_num <= REG_NUMBER)
		return (TRUE);
	return (FALSE);
}

int			get_arg_size(char op_code, t_arg_type type)
{
	if (type == REG_CODE)
		return (1);
	else if (type == DIR_CODE)
		return (g_op_tab[op_code].tdir_size);
	else if (type == IND_CODE)
		return (IND_SIZE);
	return (0);
}

int			get_ind_value(char *arena, unsigned int index,\
			char offset, t_bool mod)
{
	short	address;
	int		value;

	address = read_2_bytes(arena, index + offset);
	if (mod)
		address = address % IDX_MOD;
	value = read_4_bytes(arena, index + address);
	return (value);
}

int			get_arg_value(char *arena, t_cursor *cursor,\
			t_arg_type type, char *offset)
{
	short		address;
	int			value;

	value = 0;
	if (type == REG_CODE)
	{
		if (isregister(arena[(cursor->pos + *offset) % MEM_SIZE]))
			value = cursor->reg[arena[(cursor->pos + *offset) % MEM_SIZE]];
		else
			cursor->exec = FALSE;
	}
	else if (type == DIR_CODE)
	{
		value = read_to_int(arena, cursor->pos + *offset,\
		g_op_tab[cursor->op_code].tdir_size);
	}
	else if (type == IND_CODE)
	{
		address = read_to_int(arena, cursor->pos + *offset, IND_SIZE);
		if (cursor->op_code != LLD && cursor->op_code != LLDI)
			address = address % IDX_MOD;
		value = read_to_int(arena, cursor->pos + address, DIR_SIZE);
	}
	*offset += get_arg_size(cursor->op_code, type);
	return (value);
}
