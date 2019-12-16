/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:31:53 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/13 20:28:25 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "op_struct.h"
#include "libftprintf.h"

/*
** GLOBAL VARIABLE G_OP_TAB
** NEEDED ONLY FOR SUBSTRACT INFORMATION ABOUT OPERATIONS
*/

t_op g_op_tab[] = { {0, 0, 0, 0, 0, 0, 0},
	{"live", 1, {D}, 1, 10, 0, 4},
	{"ld", 2, {DI, R}, 2, 5, 1, 4},
	{"st", 2, {R, RI}, 3, 5, 1, 4},
	{"add", 3, {R, R, R}, 4, 10, 1, 4},
	{"sub", 3, {R, R, R}, 5, 10, 1, 4},
	{"and", 3, {RDI, RDI, R}, 6, 6, 1, 4},
	{"or", 3, {RDI, RDI, R}, 7, 6, 1, 4},
	{"xor", 3, {RDI, RDI, R}, 8, 6, 1, 4},
	{"zjmp", 1, {D}, 9, 20, 0, 2},
	{"ldi", 3, {RDI, RD, R}, 10, 25, 1, 2},
	{"sti", 3, {R, RDI, RD}, 11, 25, 1, 2},
	{"fork", 1, {D}, 12, 800, 0, 2},
	{"lld", 2, {DI, R}, 13, 10, 1, 4},
	{"lldi", 3, {RDI, RD, R}, 14, 50, 1, 2},
	{"lfork", 1, {D}, 15, 1000, 0, 2},
	{"aff", 1, {R}, 16, 2, 1, 4} };

char		get_dir_size(char op_code)
{
	return (DIR_SIZE - IND_SIZE * g_op_tab[op_code].tdir_size);
}

t_bool		possible_arg(char code, char num, t_arg_type type)
{
	char	code_arg;

	code_arg = g_op_tab[code].args[num];
	if (type == T_REG && !((( code_arg >> 4) & REG_CODE) ^ REG_CODE))
		return (TRUE);
	else if (type == T_DIR && !(((code_arg >> 2) & DIR_CODE) ^ DIR_CODE))
		return (TRUE);
	else if (type == T_IND && !((code_arg & IND_CODE) ^ IND_CODE))
		return (TRUE);
	return (FALSE);
}

t_op		get_op_struct(char op_code)
{
	return (g_op_tab[op_code]);
}

char		*get_op_name(char op_code)
{
	return (g_op_tab[op_code].name);
}

int			get_instruct_code(char *name)
{
	int i;
	int	code;
	int name_len;

	i = 1;
	code = 0;
	while (i <= NUMBER_OF_INSTR)
	{
		name_len = ft_strlen(g_op_tab[i].name);
		if (!ft_strncmp(g_op_tab[i].name, name, name_len))
			code = i;
		++i;
	}
	return (code);
}
