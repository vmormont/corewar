/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:45:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/05 22:25:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_st(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	char		reg_n;
	char		code_args;
	char		reg_arg;
	short		address;

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
			address = read_2_bytes(vm->arena, cursor->pos + 3) % IDX_MOD;
			copy_4_bytes(vm->arena, cursor->pos + address, cursor->reg[reg_n]);
		}
	}
}

static int	get_arg(t_vm *vm, t_cursor *cursor, char *offset, char num)
{
	t_arg_type	type;
	char		reg_arg;
	short		address;
	int			value;

	value = 0;
	type = get_arg_type(vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE], num);
	if (type == REG_CODE)
	{
		reg_arg = vm->arena[(cursor->pos + *offset) % MEM_SIZE];
		if (isregister(reg_arg))
			value = cursor->reg[reg_arg];
		else
			cursor->exec = FALSE;
		*offset += 1;
	}
	else if (type == DIR_CODE)
	{
		value = read_2_bytes(vm->arena, cursor->pos + *offset);
		*offset += IND_SIZE;
	}
	else if (type == IND_CODE)
	{
		address = read_2_bytes(vm->arena, cursor->pos + *offset);
		value = read_4_bytes(vm->arena, cursor->pos + (address % IDX_MOD));
		*offset += IND_SIZE;
	}
	return (value);
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	char		reg_n;
	int			address1;
	int			address2;
	char		offset;

	offset = OP_SIZE + ARGS_SIZE;
	reg_n = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (!isregister(reg_n))
		return ;
	offset += 1;
	address1 = get_arg(vm, cursor, &offset, SECOND);
	address2 = get_arg(vm, cursor, &offset, THIRD);
	if (cursor->exec)
		copy_4_bytes(vm->arena,\
		cursor->pos + ((address1 + address2) % IDX_MOD), cursor->reg[reg_n]);
}
