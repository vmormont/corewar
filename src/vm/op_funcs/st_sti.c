/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:45:30 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/17 19:28:56 by astripeb         ###   ########.fr       */
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
	reg_n = vm->arena[(cursor->pos + PRE_SIZE) % MEM_SIZE];
	cursor->step = 3;
	if (((code_args >> 4) & 3) == REG_CODE)
	{
		reg_arg = vm->arena[(cursor->pos + cursor->step) % MEM_SIZE];
		cursor->reg[reg_arg] = cursor->reg[reg_n];
	}
	else
	{
		address = read_2_bytes(vm->arena, cursor->pos + cursor->step);
		copy_4_bytes(vm->arena, cursor->pos + (address % IDX_MOD),\
		cursor->reg[reg_n]);
	}
	cursor->step += get_arg_size(cursor->op_code, (code_args >> 4) & 3);
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | st r%d %d\n", cursor->id, reg_n,\
		((code_args >> 4) & 3) == REG_CODE ? reg_arg : address);
}

static void	log_sti(t_cursor *cursor, char reg, int addr1, int addr2)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->id, reg, addr1, addr2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",\
	addr1, addr2, addr1 + addr2,\
	cursor->pos + ((addr1 + addr2) % IDX_MOD));
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	char		reg_n;
	char		code_args;
	int			address1;
	int			address2;

	code_args = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	reg_n = vm->arena[(cursor->pos + PRE_SIZE) % MEM_SIZE];
	cursor->step = 3;
	address1 = get_arg_value(vm->arena, cursor, (code_args >> 4) & 3);
	address2 = get_arg_value(vm->arena, cursor, (code_args >> 2) & 3);
	copy_4_bytes(vm->arena,\
	cursor->pos + ((address1 + address2) % IDX_MOD), cursor->reg[reg_n]);
	if (vm->options.verbos == V_OPERATIONS)
		log_sti(cursor, reg_n, address1, address2);
}
