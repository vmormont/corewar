/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_aff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:15:04 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/06 00:12:21 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_function	g_operation[] = {NULL, &op_live, &op_ld, &op_st, &op_add,\
	&op_sub, &op_and, &op_or, &op_xor, &op_zjmp, &op_ldi, &op_sti,\
	&op_fork, &op_lld, &op_lldi, &op_lfork, &op_aff};

void		op_live(t_vm *vm, t_cursor *cursor)
{
	int		n;
	t_champ	*champ;

	vm->num_live_op += 1;
	cursor->cycle_live = vm->cycles;
	n = read_4_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (n == cursor->reg[1])
	{
		if ((champ = get_champ_by_id(vm->champs, n)))
		{
			champ->last_live = vm->cycles;
			champ->lives_in_period += 1;
		}
	}
}

void		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	short	address;

	if (cursor->carry)
	{
		address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE) % IDX_MOD;
		cursor->pos = (cursor->pos + address) % MEM_SIZE;
		cursor->step = 0;
	}
	else
		cursor->step = 1;
}

void		op_aff(t_vm *vm, t_cursor *cursor)
{
	char	reg_n;

	reg_n = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	if (isregister(reg_n))
	{
		if (vm->options.aff)
			ft_printf("aff (%c)\n", (char)cursor->reg[reg_n]);
	}
}
