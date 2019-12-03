/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/03 21:23:52 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_ldi_lldi(char *arena, t_cursor *cursor, char type, int *offset)
{
	int		res;
	char	reg_num;
	short	address;

	if (type == REG_CODE)
	{
		reg_num = arena[cursor->pos + *offset];
		if (isregister(reg_num))
			res = cursor->reg[reg_num];
		else
			cursor->exec = FALSE;
		*offset += 1;
	}
	else if (type == DIR_CODE)
	{
		res = read_2_bytes(arena, cursor->pos + *offset);
		*offset += 2;
	}
	else if (type == IND_CODE)
	{
		address = read_2_bytes(arena, cursor->pos + *offset) % IDX_MOD;
		res = read_4_bytes(arena, cursor->pos + address);
		*offset += 2;
	}
	return (res);
}

void op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	char	num_reg;
	int		offset;

	offset = 2;
	code_arg = vm->arena[cursor->pos + 1];
	num1 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	num2 = arg_ldi_lldi(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	num_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(num_reg) && cursor->exec)
		cursor->reg[num_reg] = read_4_bytes(vm->arena, (num1 + num2) % IDX_MOD);
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
		cursor->reg[num_reg] = read_4_bytes(vm->arena, (num1 + num2));
}
