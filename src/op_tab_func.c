/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 10:23:16 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/09 13:15:29 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	*create_op_tab(void)
{
	t_op	*op_tab;

	if (!(op_tab = (t_op*)malloc(sizeof(t_op) * (NUMBER_OF_INSTR + 1))))
		return (NULL);
	op_tab[0] = (t_op){0, 0, 0, 0, 0, 0, 0};
	op_tab[1] = (t_op){"live", 1, {D}, 1, 10, 0, 0};
	op_tab[2] = (t_op){"ld", 2, {DI, R}, 2, 5, 1, 0};
	op_tab[3] = (t_op){"st", 2, {R, RI}, 3, 5, 1, 0};
	op_tab[4] = (t_op){"add", 3, {R, R, R}, 4, 10, 1, 0};
	op_tab[5] = (t_op){"sub", 3, {R, R, R}, 5, 10, 1, 0};
	op_tab[6] = (t_op){"and", 3, {RDI, RDI, R}, 6, 6, 1, 0};
	op_tab[7] = (t_op){"or", 3, {RDI, RDI, R}, 7, 6, 1, 0};
	op_tab[8] = (t_op){"xor", 3, {RDI, RDI, R}, 8, 6, 1, 0};
	op_tab[9] = (t_op){"zjmp", 1, {D}, 9, 20, 0, 1};
	op_tab[10] = (t_op){"ldi", 3, {RDI, RD, R}, 10, 25, 1, 1};
	op_tab[11] = (t_op){"sti", 3, {R, RDI, RD}, 11, 25, 1, 1};
	op_tab[12] = (t_op){"fork", 1, {D}, 12, 800, 0, 1};
	op_tab[13] = (t_op){"lld", 2, {DI, R}, 13, 10, 1, 0};
	op_tab[14] = (t_op){"lldi", 3, {RDI, RD, R}, 14, 50, 1, 1};
	op_tab[15] = (t_op){"lfork", 1, {D}, 15, 1000, 0, 1};
	op_tab[16] = (t_op){"aff", 1, {R}, 16, 2, 1, 0};
	return (op_tab);
}

int		get_op_code(t_op *op_tab, char *name)
{
	int i;

	i = 1;
	while (i <= NUMBER_OF_INSTR)
	{
		if (!ft_strcmp(name, op_tab[i].name))
			return (op_tab[i].code);
		++i;
	}
	return (0);
}

int		possible_arg(char arg, char mask)
{
	if (arg == T_REG && !(((mask >> 4) & T_REG) ^ T_REG))
		return (1);
	else if (arg == T_DIR && !(((mask >> 2) & T_DIR) ^ T_DIR))
			return (1);
	else if (arg == T_IND && !((mask & 3) ^ 3))
			return (1);
	return (0);
}

void	print_op_tab(t_op *op_tab)
{
	int i;

	i = 0;
	while (i < NUMBER_OF_INSTR)
	{
		ft_printf("[%2d] %-5s %2d %5d\n", op_tab[i].code, op_tab[i].name,\
		op_tab[i].num_args, op_tab[i].cycles2go);
		++i;
	}
}
