/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/03 17:53:29 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_ldi_lldi(char *arena, t_cursor *cursor, char type, int *offset)
{
	int		res;
	char	reg_num;
	int		shift;

	if (type == DIR_CODE)
	{
		res = read_2_bytes(arena, cursor->pos + *offset);
		*offset += 2;
	}
	else if (type == REG_CODE)
	{
		reg_num = arena[cursor->pos + *offset];
		res = isregister(reg_num) ? cursor->reg[reg_num] : 0;
		if (!isregister(reg_num))
			cursor->exec = FALSE;
		*offset += 1;
	}
	else if (type == IND_CODE)
	{
		if (cursor->op_code == 0x0A)
			shift = read_2_bytes(arena, cursor->pos + *offset) % IDX_MOD;
		else
			shift = read_2_bytes(arena, cursor->pos + *offset);
		res = read_4_bytes(arena, cursor->pos + shift);
	}
	return (res);
}

void op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	int		num_reg;
	int		offset;

	offset = 2;
	code_arg = vm->arena[cursor->pos + 1];
	num1 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	num2 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	num_reg = vm->arena[cursor->pos + offset];
	if (isregister(num_reg) && cursor->exec)
		cursor->reg[num_reg] = (num1 + num2) % IDX_MOD;
	//offset++;
	//ft_printf("ldi start step = %d   ", cursor->step);
	//cursor->step = offset;
	//ft_printf("ldi finish step = %d   ", cursor->step);
	//ft_printf("op code = %d, 1: %d, 2: %d, 3: %d, step = %d\n", cursor->op_code,\
	get_arg_type(code_arg, FIRST), get_arg_type(code_arg, SECOND),\
	get_arg_type(code_arg, THIRD), cursor->step);
}

void op_lldi(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	int		num_reg;
	int		offset;

	offset = 2;
	code_arg = vm->arena[cursor->pos + 1];
	num1 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	num2 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	num_reg = vm->arena[cursor->pos + offset];
	if (isregister(num_reg) && cursor->exec)
		cursor->reg[num_reg] = (num1 + num2);
	//offset++;
	//ft_printf("lldi start step = %d   ", cursor->step);
	//cursor->step = offset;
	//ft_printf("ldi finish step = %d   ", cursor->step);
	//ft_printf("op code = %d, 1: %d, 2: %d, 3: %d, step = %d\n", cursor->op_code,\
	get_arg_type(code_arg, FIRST), get_arg_type(code_arg, SECOND),\
	get_arg_type(code_arg, THIRD), cursor->step);
}
