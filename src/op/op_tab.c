/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:31:53 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 11:10:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "op_struct.h"

/*
** GLOBAL VARIABLE G_OP_TAB
** NEEDED ONLY FOR SUBSTRACT INFORMATION ABOUT OPERATIONS
*/

t_op g_op_tab[] = { {0, 0, 0, 0, 0, 0, 0},
	{"live", 1, {D}, 1, 10, 0, 0},
	{"ld", 2, {DI, R}, 2, 5, 1, 0},
	{"st", 2, {R, RI}, 3, 5, 1, 0},
	{"add", 3, {R, R, R}, 4, 10, 1, 0},
	{"sub", 3, {R, R, R}, 5, 10, 1, 0},
	{"and", 3, {RDI, RDI, R}, 6, 6, 1, 0},
	{"or", 3, {RDI, RDI, R}, 7, 6, 1, 0},
	{"xor", 3, {RDI, RDI, R}, 8, 6, 1, 0},
	{"zjmp", 1, {D}, 9, 20, 0, 1},
	{"ldi", 3, {RDI, RD, R}, 10, 25, 1, 1},
	{"sti", 3, {R, RDI, RD}, 11, 25, 1, 1},
	{"fork", 1, {D}, 12, 800, 0, 1},
	{"lld", 2, {DI, R}, 13, 10, 1, 0},
	{"lldi", 3, {RDI, RD, R}, 14, 50, 1, 1},
	{"lfork", 1, {D}, 15, 1000, 0, 1},
	{"aff", 1, {R}, 16, 2, 1, 0} };

int		possible_arg(t_arg_type type, char mask)
{
	if (type == T_REG && !(((mask >> 4) & 1) ^ 1))
		return (1);
	else if (type == T_DIR && !(((mask >> 2) & 2) ^ 2))
		return (1);
	else if (type == T_IND && !((mask & 3) ^ 3))
		return (1);
	return (0);
}
