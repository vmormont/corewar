/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/13 20:25:03 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_and(t_vm *vm, t_cursor *cursor)
{
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3, &offset);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3, &offset);

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
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3, &offset);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3, &offset);

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
	int			arg1;
	int			arg2;
	char		arg3;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	//получаем значение из первого и второго аргумента
	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3, &offset);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3, &offset);

	//получаем номер регистра для третьего аргумента
	arg3 = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(arg3) && cursor->exec)
	{
		cursor->reg[arg3] = arg1 ^ arg2;
		cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;
	}
}
