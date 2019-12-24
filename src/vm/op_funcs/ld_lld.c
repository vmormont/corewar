/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/24 12:52:55 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ld(t_vm *vm, t_cursor *cursor)
{
	int			value;
	short		reg;
	char		code_args;

	cursor->step = PRE_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3));
	reg = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
	cursor->reg[reg] = value;
	cursor->step += ARENA_REG_SIZE;
	cursor->carry = value ? FALSE : TRUE;
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | ld %d r%d\n", cursor->id, value, reg);
}

void	op_lld(t_vm *vm, t_cursor *cursor)
{
	int			value;
	short		reg;
	char		code_args;

	cursor->step = PRE_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3));
	reg = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
	cursor->reg[reg] = value;
	cursor->step += ARENA_REG_SIZE;
	cursor->carry = value ? FALSE : TRUE;
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | lld %d r%d\n", cursor->id, value, reg);
}
