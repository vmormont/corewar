/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:45:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/13 20:41:40 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_st(t_vm *vm, t_cursor *cursor)
{
	char		reg_n;
	char		reg_arg;
	short		address;
	char		code_args;

	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	reg_n = vm->arena[(cursor->pos + OP_SIZE + ARGS_SIZE) % MEM_SIZE];
	if (isregister(reg_n))
	{
		if (((code_args >> 4) & 3) == REG_CODE)
		{
			reg_arg = vm->arena[(cursor->pos + 3) % MEM_SIZE];
			if (isregister(reg_arg))
				cursor->reg[reg_arg] = cursor->reg[reg_n];
		}
		else
		{
			address = read_2_bytes(vm->arena, cursor->pos + 3) % IDX_MOD;
			copy_4_bytes(vm->arena, cursor->pos + address, cursor->reg[reg_n]);
		}
	}
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	char		reg_n;
	char		code_args;
	int			address1;
	int			address2;
	char		offset;

	offset = OP_SIZE + ARGS_SIZE;
	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	reg_n = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (!isregister(reg_n))
		return ;
	offset += 1;
	address1 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3, &offset);
	address2 = get_arg_value(vm->arena, cursor, (code_args >> 2) & 3, &offset);
	if (cursor->exec)
		copy_4_bytes(vm->arena,\
		cursor->pos + ((address1 + address2) % IDX_MOD), cursor->reg[reg_n]);
}
