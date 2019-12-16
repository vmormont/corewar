/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 12:07:23 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/14 12:41:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

static t_bool	validation_arg(char op_code, t_arg_type type, char num_arg)
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

static t_bool	calc_step(t_cursor *cursor, char code_arg)
{
	int			i;
	char		step;
	t_bool		exec;
	t_arg_type	type;

	i = 0;
	exec = TRUE;
	cursor->step = OP_SIZE + ARGS_SIZE;
	while (i < g_op_tab[cursor->op_code].num_args)
	{
		type = (code_arg >> (6 - (2 * i)) & 3);
		if (type == REG_CODE)
			cursor->step += 1;
		else if (type == DIR_CODE)
			cursor->step += g_op_tab[cursor->op_code].tdir_size;
		else if (type == IND_CODE)
			cursor->step += IND_SIZE;
		exec = validation_arg(cursor->op_code, type, i) ? exec : FALSE;
		++i;
	}
	return (exec);
}

t_bool			check_op_code_and_type_args(t_cursor *cursor, char *arena)
{
	t_bool		exec;
	char		i;

	exec = TRUE;
	if (cursor->op_code < 1 || cursor->op_code > 16)
	{
		cursor->step = 1;
		return (FALSE);
	}
	if (g_op_tab[cursor->op_code].code_args)
		exec = calc_step(cursor, arena[(cursor->pos + OP_SIZE) % MEM_SIZE]);
	else
		cursor->step = OP_SIZE + g_op_tab[cursor->op_code].tdir_size;
	return (exec);
}
