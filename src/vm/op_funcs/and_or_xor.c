/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 16:36:53 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_and(t_vm *vm, t_cursor *cursor)
{
	int			arg1;
	int			arg2;
	short		arg3;
	char		code_args;

	cursor->step = PRE_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];

	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3);
	arg3 = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
	cursor->reg[arg3] = arg1 & arg2;
	cursor->step += ARENA_REG_SIZE;
	cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;

	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | and %d %d r%d\n", cursor->id, arg1, arg2, arg3);
}

void		op_or(t_vm *vm, t_cursor *cursor)
{
	int			arg1;
	int			arg2;
	short		arg3;
	char		code_args;

	cursor->step = PRE_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3);
	arg3 = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
	cursor->reg[arg3] = arg1 | arg2;
	cursor->step += ARENA_REG_SIZE;
	cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;

	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | or %d %d r%d\n", cursor->id, arg1, arg2, arg3);
}

void		op_xor(t_vm *vm, t_cursor *cursor)
{
	int			arg1;
	int			arg2;
	short		arg3;
	char		code_args;

	cursor->step = PRE_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];

	arg1 = get_arg_value(vm->arena, cursor, (code_args >> 6) & 3);
	arg2 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3);
	arg3 = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
	cursor->reg[arg3] = arg1 ^ arg2;
	cursor->step += ARENA_REG_SIZE;
	cursor->carry = cursor->reg[arg3] ? FALSE : TRUE;

	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | xor %d %d r%d\n", cursor->id, arg1, arg2, arg3);
}
