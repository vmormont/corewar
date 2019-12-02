/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:01:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/02 16:17:35 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static int	get_ind_value(char *arena, int index, char offset)
{
	short	address;
	int		value;

	address = read_2_bytes(arena, index + offset);
	value = read_4_bytes(arena, index + (address % IDX_MOD));
	return (value);
}
//надо сделать разницу между ld и lld

void op_ld(t_vm *vm, t_cursor  *cursor)
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
		num = get_ind_value(vm->arena, cursor->pos, 2);
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = FALSE;
		else 
			cursor->carry = TRUE;
	}
	ft_printf("op code = %d, 1: %d, 2: %d, 3: %d, step = %d\n", cursor->op_code,\
	get_arg_type(code_arg, FIRST), get_arg_type(code_arg, SECOND),\
	get_arg_type(code_arg, THIRD), cursor->step);
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
		num = get_ind_value(vm->arena, cursor->pos, 2);
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = FALSE;
		else 
			cursor->carry = TRUE;
	}
	ft_printf("op code = %d, 1: %d, 2: %d, 3: %d, step = %d\n", cursor->op_code,\
	get_arg_type(code_arg, FIRST), get_arg_type(code_arg, SECOND),\
	get_arg_type(code_arg, THIRD), cursor->step);
}
