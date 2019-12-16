/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:27:58 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/16 22:24:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void op_ld(t_vm *vm, t_cursor  *cursor)
{
	int			value;
	char		reg;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3), &offset);
	reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(reg) && cursor->exec)
	{
		cursor->reg[reg] = value;
		cursor->carry = value ? FALSE : TRUE;
		if (vm->options.verbos == V_OPERATIONS)
			ft_printf("P %4d | ld %d r%d\n", cursor->id, value, reg);
	}
}

void op_lld(t_vm *vm, t_cursor  *cursor)
{
	int			value;
	char		reg;
	char		offset;
	char		code_args;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	value = get_arg_value(vm->arena, cursor, ((code_args >> 6) & 3), &offset);
	reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(reg) && cursor->exec)
	{
		cursor->reg[reg] = value;
		cursor->carry = value ? FALSE : TRUE;
		if (vm->options.verbos == V_OPERATIONS)
			ft_printf("P %4d | lld %d r%d\n", cursor->id, value, reg);
	}
}
