/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:52:56 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/03 21:05:52 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_add(t_vm *vm, t_cursor *cursor)
{
	char		f_reg;
	char		s_reg;
	char		t_reg;

	f_reg = vm->arena[(cursor->pos + 2) % MEM_SIZE];
	s_reg = vm->arena[(cursor->pos + 3) % MEM_SIZE];
	if (isregister(f_reg) && isregister(s_reg))
	{
		t_reg = vm->arena[(cursor->pos + 4) % MEM_SIZE];
		if (isregister(t_reg))
		{
			cursor->reg[t_reg] = cursor->reg[f_reg] + cursor->reg[s_reg];
			cursor->carry = cursor->reg[t_reg] ? FALSE : TRUE;
		}
	}
}

void		op_sub(t_vm *vm, t_cursor *cursor)
{
	char		f_reg;
	char		s_reg;
	char		t_reg;

	f_reg = vm->arena[(cursor->pos + 2) % MEM_SIZE];
	s_reg = vm->arena[(cursor->pos + 3) % MEM_SIZE];
	if (isregister(f_reg) && isregister(s_reg))
	{
		t_reg = vm->arena[(cursor->pos + 4) % MEM_SIZE];
		if (isregister(t_reg))
		{
			cursor->reg[t_reg] = cursor->reg[f_reg] - cursor->reg[s_reg];
			cursor->carry = cursor->reg[t_reg] ? FALSE : TRUE;
		}
	}
}
