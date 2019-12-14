/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_aff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:15:04 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/14 17:50:32 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_live(t_vm *vm, t_cursor *cursor)
{
	int		n;
	t_champ	*champ;

	vm->num_live_op += 1;
	cursor->cycle_live = vm->cycles;
	n = read_4_bytes(vm->arena, cursor->pos + OP_SIZE);
	if ((champ = get_champ_by_id(vm->champs, n)))
	{
		champ->last_live = vm->cycles;
		vm->winner = n;
		champ->lives_in_period += 1;
		if (vm->options.verbos == V_LIVE)
			ft_printf("Player %d (%s) is said to be alive\n",\
			-(champ->id), champ->name);
	}
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | live %d\n", cursor->id, n);
}

void		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	short	address;

	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (cursor->carry)
	{
		cursor->pos = (cursor->pos + (address % IDX_MOD)) % MEM_SIZE;
		cursor->step = 0;
	}
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | zjmp %d %s\n", cursor->id, address,\
		cursor->carry ? "OK" : "FAILED");
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
