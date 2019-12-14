/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/14 17:53:24 by astripeb         ###   ########.fr       */
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
		if (vm->options.verbos == V_OPERATIONS)
			ft_printf("P %4d | or %d %d r%d\n", cursor->id, arg1, arg2, arg3);
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
		if (vm->options.verbos == V_OPERATIONS)
			ft_printf("P %4d | xor %d %d r%d\n", cursor->id, arg1, arg2, arg3);
	}
}
