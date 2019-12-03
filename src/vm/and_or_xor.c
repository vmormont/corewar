/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/03 20:48:14 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_ind_value(char *arena, unsigned int index, char offset)
{
	short	address;
	int		value;

	address = read_2_bytes(arena, index + offset);
	value = read_4_bytes(arena, index + (address % IDX_MOD));
	return (value);
}

static int	get_arg_value(char *arena, t_cursor *cursor, char *offset, char num)
{
	int			value;
	char		reg_num;
	t_arg_type	type;

	value = 0;
	type = get_arg_type(arena[(cursor->pos + OP_SIZE) % MEM_SIZE], num);
	if (type == REG_CODE)
	{
		reg_num = arena[(cursor->pos + *offset) % MEM_SIZE];
		if (isregister(reg_num))
			value = cursor->reg[reg_num];
		else
			cursor->exec = FALSE;
		*offset += 1;
	}
	if (type == DIR_CODE)
	{
		value = read_4_bytes(arena, cursor->pos + *offset);
		*offset += DIR_SIZE;
	}
	else if (type == IND_CODE)
	{
		value = get_ind_value(arena, cursor->pos, *offset);
		*offset += IND_SIZE;
	}
	return (value);
}

void		op_and(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;

	offset = OP_SIZE + ARGS_SIZE;
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, &offset, FIRST);
	arg2 = get_arg_value(vm->arena, cursor, &offset, SECOND);

	//получаем номер регистра для третьего аргумента
	arg3 = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(arg3) && cursor->exec)
	{
		cursor->reg[arg3] = arg1 & arg2;
		cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;
	}
}

void		op_or(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;

	offset = 2;
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, &offset, FIRST);
	arg2 = get_arg_value(vm->arena, cursor, &offset, SECOND);

	//получаем номер регистра для третьего аргумента
	arg3 = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(arg3) && cursor->exec)
	{
		cursor->reg[arg3] = arg1 | arg2;
		cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;
	}
}

void		op_xor(t_vm *vm, t_cursor *cursor)
{
	t_arg_type	type;
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;

	offset = 2;
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, &offset, FIRST);
	arg2 = get_arg_value(vm->arena, cursor, &offset, SECOND);

	//получаем номер регистра для третьего аргумента
	arg3 = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(arg3) && cursor->exec)
	{
		cursor->reg[arg3] = arg1 ^ arg2;
		cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;
	}
}
