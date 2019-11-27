/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/27 20:44:27 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	first_arg_ldi_lldi(char *arena, t_cursor *cursor, char type)
{
	int		res;
	char	reg_num;
	int		shift;

	cursor->step = 2;
	if (type == DIR_CODE)
	{
		res = read_2_bytes(arena, cursor->pos + cursor->step);
		cursor->step += 2;
	}
	else if (type == REG_CODE)
	{
		reg_num = arena[cursor->pos + cursor->step];
		res = cursor->reg[reg_num];
		cursor->step += 1;
	}
	else if (type == IND_CODE)
	{
		shift = read_2_bytes(arena, cursor->pos + cursor->step) % IDX_MOD;
		res = read_4_bytes(arena, cursor->pos + shift);
	}	
	return (res);
}

static int	second_arg_ldi_lldi(char *arena, t_cursor *cursor, char type)
{
	int		res;
	char	reg_num;
	int		shift;

	if (type == DIR_CODE)
	{
		res = read_2_bytes(arena, cursor->pos + cursor->step);
		cursor->step += 2;
	}
	else if (type == REG_CODE)
	{
		reg_num = arena[cursor->pos + cursor->step];
		res = cursor->reg[reg_num];
		cursor->step += 1;
	}
	return (res);
}

void op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	num1 = first_arg_ldi_lldi(vm->arena, cursor, (code_arg >> 6) & 3);
	num2 = second_arg_ldi_lldi(vm->arena, cursor, (code_arg >> 4) & 3);
	num_reg = read_4_bytes(vm->arena, cursor->pos + cursor->step);
	cursor->reg[num_reg] = (num1 + num2) % IDX_MOD;
}

void op_lldi(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	num1 = first_arg_ldi_lldi(vm->arena, cursor, (code_arg >> 6) & 3);
	num2 = second_arg_ldi_lldi(vm->arena, cursor, (code_arg >> 4) & 3);
	num_reg = read_4_bytes(vm->arena, cursor->pos + cursor->step);
	cursor->reg[num_reg] = (num1 + num2);
}
