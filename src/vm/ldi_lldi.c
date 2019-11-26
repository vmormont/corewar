/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/26 20:29:49 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	first_arg_ldi(char *arena, t_cursor *cursor, char type, char long)
{
	int		res;
	char	reg_num;

	cursor->step = 2;
	if (type == T_DIR)
	{
		res = read_2_bytes(arena, cursor->pos + 2);
		cursor->step += 2;
	}
	else if (type == T_REG)
	{
		reg_num = arena[cursor->pos + 2];
		res = cursor->reg[reg_num];
		cursor->step += 1;
	}
	else if (type == T_IND)
}

void op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		num;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	num = first_arg_ldi(vm->arena, cursor, (code_arg >> 6) & 3, 0)
	if (((code_arg >> 6) & 3) == T_REG)
	{
		num_reg = vm->arena[cursor->pos + 2];
		num = cursor->reg[num_reg];
	}
	else if(((code_arg >> 6) & 3) == T_DIR)
	{
		num = read_2_bytes(vm->arena, (cursor->pos + 2)) % IDX_MOD;
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (num_reg > 0 && num_reg < 17)
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = 0;
		else 
			cursor->carry = 1;
	}
	//ft_printf("num = %d, num reg = %d, cursor reg = %d\n", num, num_reg, cursor->reg[num_reg]);
}

void op_lldi(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	if (((code_arg >> 6) & 3) == T_DIR)
	{
		num = read_4_bytes(vm->arena, (cursor->pos + 2));
		num_reg = vm->arena[cursor->pos + 6];
	}
	else if(((code_arg >> 6) & 3) == T_IND)
	{
		num = read_2_bytes(vm->arena, (cursor->pos + 2));
		num_reg = vm->arena[cursor->pos + 4];
	}
	if (num_reg > 0 && num_reg < 17)
	{
		cursor->reg[num_reg] = num;
		if (num)
			cursor->carry = 0;
		else 
			cursor->carry = 1;
	}
	//ft_printf("num = %d, num reg = %d, cursor reg = %d\n", num, num_reg, cursor->reg[num_reg]);
}
