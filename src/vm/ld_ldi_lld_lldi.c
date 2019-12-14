/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi_lld_lldi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/13 21:49:03 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	char	num_reg;
	char	offset;

	offset = 2;
	code_arg = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	num1 = get_arg_value(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	num2 = get_arg_value(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	num_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(num_reg) && cursor->exec)
		cursor->reg[num_reg] = read_4_bytes(vm->arena, cursor->pos\
		+ ((num1 + num2) % IDX_MOD));
}

void op_lldi(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num1;
	int		num2;
	int		num_reg;
	char	offset;

	offset = 2;
	code_arg = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	num1 = get_arg_value(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	num2 = get_arg_value(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	num_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(num_reg) && cursor->exec)
	{
		cursor->reg[num_reg] = read_4_bytes(vm->arena, cursor->pos + (num1 + num2));
		cursor->carry = cursor->reg[num_reg] ? FALSE : TRUE;
	}
}

void op_ld(t_vm *vm, t_cursor  *cursor)
{
	int			value;
	char		num_reg;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3), &offset);
	num_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(num_reg) && cursor->exec)
	{
		cursor->reg[num_reg] = value;
		cursor->carry = value ? FALSE : TRUE;
	}
}

void op_lld(t_vm *vm, t_cursor  *cursor)
{
	int			value;
	char		num_reg;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3), &offset);
	num_reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(num_reg) && cursor->exec)
	{
		cursor->reg[num_reg] = value;
		cursor->carry = value ? FALSE : TRUE;
	}
}
