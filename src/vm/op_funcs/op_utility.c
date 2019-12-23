/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:41:19 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 16:53:50 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

int			read_4_bytes(char *arena, unsigned int index)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (i < DIR_SIZE)
	{
		num = (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		++i;
		++index;
	}
	return (num);
}

short		read_2_bytes(char *arena, unsigned int index)
{
	int		i;
	short	num;

	num = 0;
	i = 0;
	while (i < IND_SIZE)
	{
		num = (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		++i;
		++index;
	}
	return (num);
}

void		copy_4_bytes(char *arena, unsigned int index, int num)
{
	int		i;
	char	offset;

	i = 0;
	offset = 24;
	while (i < REG_SIZE)
	{
		arena[index % MEM_SIZE] = (uint8_t)((num >> offset) & 0xFF);
		++i;
		++index;
		offset = offset - __CHAR_BIT__;
	}
}

int			get_arg_size(short op_code, t_arg_type type)
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
	short		reg_n;

	value = 0;
	reg_n = arena[(cursor->pos +cursor->step) % MEM_SIZE];
	if (type == REG_CODE)
		value = cursor->reg[reg_n];
	else if (type == DIR_CODE)
	{
		if (g_op_tab[cursor->op_code].tdir_size == IND_SIZE)
			value = read_2_bytes(arena, cursor->pos + cursor->step);
		else
			value = read_4_bytes(arena, cursor->pos + cursor->step);
	}
	else if (type == IND_CODE)
	{
		address = read_2_bytes(arena, cursor->pos + cursor->step);
		if (cursor->op_code != LLD && cursor->op_code != LLDI)
			address = address % IDX_MOD;
		value = read_4_bytes(arena, cursor->pos + address);
	}
	cursor->step += get_arg_size(cursor->op_code, type);
	return (value);
}
