/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:45:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/28 14:44:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_st(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	char		reg_n;
	char		code_args;
	char		reg_arg;
	short		ind_val;

	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	reg_n = vm->arena[(cursor->pos + OP_SIZE + ARGS_SIZE) % MEM_SIZE];
	if (isregister(reg_n))
	{
		type = get_arg_type(code_args, SECOND);
		if (type == REG_CODE)
		{
			reg_arg = vm->arena[(cursor->pos + 3) % MEM_SIZE];
			if (isregister(reg_arg))
				cursor->reg[reg_arg] = cursor->reg[reg_n];
		}
		else if (type == IND_CODE)
		{
			ind_val = read_2_bytes(vm->arena, cursor->pos + 3) % IDX_MOD;
			copy_4_bytes(vm->arena, cursor->pos + ind_val, cursor->reg[reg_n]);
		}
	}
}

static int	get_third_arg(t_vm *vm, t_cursor *cursor, t_arg_type s_type)
{
	t_arg_type	type;
	char		offset;
	char		reg_arg;
	int			value;

	offset = OP_SIZE + ARGS_SIZE + 1 + (s_type == T_REG ? REG_SIZE : IND_SIZE);
	type = get_arg_type(vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE], THIRD);
	if (type == REG_CODE)
	{
		reg_arg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
		if (isregister(reg_arg))
			value = cursor->reg[reg_arg];
		else
			cursor->exec = FALSE;
	}
	else if (type == DIR_CODE)
		value = read_2_bytes(vm->arena, cursor->pos + offset);
	return (value);
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	char		reg_n;
	char		reg_arg;
	int			address;

	reg_n = vm->arena[(cursor->pos + OP_SIZE + ARGS_SIZE) % MEM_SIZE];
	if (!isregister(reg_n))
		return ;
	type = get_arg_type(vm->arena[(cursor->pos + 1) % MEM_SIZE], SECOND);
	if (type == REG_CODE)
	{
		reg_arg = vm->arena[(cursor->pos + 3) % MEM_SIZE];
		if (!isregister(reg_arg))
			return ;
		address = cursor->reg[reg_arg];
	}
	else if (type == IND_CODE)
		address = read_2_bytes(vm->arena, cursor->pos + 3) + cursor->pos;
	else if (type == DIR_CODE)
		address = read_2_bytes(vm->arena, cursor->pos + 3);
	address += get_third_arg(vm, cursor, type);
	address = address % IDX_MOD;
	if (cursor->exec)
		copy_4_bytes(vm->arena, cursor->pos + address, cursor->reg[reg_n]);
}
