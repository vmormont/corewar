/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:01:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/28 12:03:23 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void op_ld(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	if (((code_arg >> 6) & 3) == DIR_CODE)
	{
		num = read_4_bytes(vm->arena, (cursor->pos + 2)) % IDX_MOD;
		num_reg = vm->arena[cursor->pos + 6];
	}
	else if(((code_arg >> 6) & 3) == IND_CODE)
	{
		num = read_2_bytes(vm->arena, (cursor->pos + 2)) % IDX_MOD;
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = 0;
		else 
			cursor->carry = 1;
	}
}

void op_lld(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	if (((code_arg >> 6) & 3) == DIR_CODE)
	{
		num = read_4_bytes(vm->arena, (cursor->pos + 2));
		num_reg = vm->arena[cursor->pos + 6];
	}
	else if(((code_arg >> 6) & 3) == IND_CODE)
	{
		num = read_2_bytes(vm->arena, (cursor->pos + 2));
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = 0;
		else 
			cursor->carry = 1;
	}
}
