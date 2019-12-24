/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 12:07:23 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/24 13:55:25 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op		g_op_tab[];

static t_bool	isregister(char reg_num)
{
	if (reg_num > 0 && reg_num <= REG_NUMBER)
		return (TRUE);
	return (FALSE);
}

static t_bool	valid_arg(short op_code, t_arg_type type, short num_arg)
{
	char	code_arg;

	code_arg = g_op_tab[op_code].args[num_arg];
	if (type == REG_CODE && !(((code_arg >> 4) & REG_CODE) ^ REG_CODE))
		return (TRUE);
	else if (type == DIR_CODE && !(((code_arg >> 2) & DIR_CODE) ^ DIR_CODE))
		return (TRUE);
	else if (type == IND_CODE && !((code_arg & IND_CODE) ^ IND_CODE))
		return (TRUE);
	return (FALSE);
}

static void		calc_step(char *arena, t_cursor *cursor)
{
	int			i;
	t_arg_type	type;
	char		code_args;

	i = 0;
	cursor->step = PRE_SIZE;
	code_args = arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	while (i < g_op_tab[cursor->op_code].num_args)
	{
		type = (code_args >> (6 - (2 * i))) & 3;
		if (type == REG_CODE)
			cursor->step += ARENA_REG_SIZE;
		else if (type == DIR_CODE)
			cursor->step += g_op_tab[cursor->op_code].tdir_size;
		else if (type == IND_CODE)
			cursor->step += IND_SIZE;
		++i;
	}
}

static t_bool	valid_args(char *arena, t_cursor *cursor, char code_args)
{
	int			i;
	char		offset;
	t_arg_type	type;

	i = 0;
	offset = PRE_SIZE;
	while (i < g_op_tab[cursor->op_code].num_args)
	{
		type = (code_args >> (6 - (2 * i))) & 3;
		if (!valid_arg(cursor->op_code, type, i))
			return (FALSE);
		if (type == REG_CODE)
		{
			if (!isregister(arena[(cursor->pos + offset) % MEM_SIZE]))
				return (FALSE);
			offset += ARENA_REG_SIZE;
		}
		else if (type == DIR_CODE)
			offset += g_op_tab[cursor->op_code].tdir_size;
		else
			offset += IND_SIZE;
		++i;
	}
	return (TRUE);
}

t_bool			check_op_code_and_type_args(t_cursor *cursor, char *arena)
{
	t_bool		exec;

	exec = TRUE;
	if (cursor->op_code < 1 || cursor->op_code > 16)
	{
		cursor->step = 1;
		return (FALSE);
	}
	if (g_op_tab[cursor->op_code].code_args)
		exec = valid_args(arena, cursor, arena[(cursor->pos + OP_SIZE)\
		% MEM_SIZE]);
	else
		cursor->step = OP_SIZE + g_op_tab[cursor->op_code].tdir_size;
	if (!exec)
		calc_step(arena, cursor);
	return (exec);
}
