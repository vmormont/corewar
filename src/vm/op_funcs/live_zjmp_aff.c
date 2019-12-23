/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_aff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:15:04 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 16:35:33 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_live(t_vm *vm, t_cursor *cursor)
{
	int		n;
	t_champ	*champ;

	cursor->step = 5;
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
	if (vm->visual)
		vis_live(vm, cursor->pos, cursor->color);
}

void		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	short	address;

	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (cursor->carry)
		cursor->step = address % IDX_MOD;

	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | zjmp %d %s\n", cursor->id, address,\
		cursor->carry ? "OK" : "FAILED");
}

void		op_aff(t_vm *vm, t_cursor *cursor)
{
	short	reg_n;

	reg_n = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	if (vm->options.aff)
			ft_printf("aff (%c)\n", (char)cursor->reg[reg_n]);
	cursor->step = 3;
}
