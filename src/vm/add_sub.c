/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:52:56 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/02 16:11:29 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_add(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	char		f_reg;
	char		s_reg;
	char		t_reg;
	char		offset;

	offset = OP_SIZE + ARGS_SIZE;
	f_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	++offset;
	s_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	++offset;
	if (isregister(f_reg) && isregister(s_reg))
	{
		t_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
		if (isregister(t_reg))
		{
			cursor->reg[t_reg] = cursor->reg[f_reg] + cursor->reg[s_reg];
			if (cursor->reg[t_reg])
				cursor->carry = FALSE;
			else
				cursor->carry = TRUE;
		}
	}
	ft_printf("op code = %d, 1: 1, 2: 1, 3: 1, step = %d\n", cursor->op_code,\
	cursor->step);
}

void		op_sub(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	char		f_reg;
	char		s_reg;
	char		t_reg;
	char		offset;

	offset = OP_SIZE + ARGS_SIZE;
	f_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	++offset;
	s_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	++offset;
	if (isregister(f_reg) && isregister(s_reg))
	{
		t_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
		if (isregister(t_reg))
		{
			cursor->reg[t_reg] = cursor->reg[f_reg] - cursor->reg[s_reg];
			if (cursor->reg[t_reg])
				cursor->carry = FALSE;
			else
				cursor->carry = TRUE;
		}
	}
	ft_printf("op code = %d, 1: 1, 2: 1, 3: 1, step = %d\n", cursor->op_code,\
	cursor->step);
}
