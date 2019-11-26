/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_aff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:15:04 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/26 19:32:07 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define OP_SIZE 1

void		op_live(t_vm *vm, t_cursor *cursor)
{
	int		n;
	t_champ	*champ;

	n = read_4_bytes(vm->arena, cursor->pos + 1);
	if (n == cursor->reg[1])
	{
		cursor->cycle_live = vm->cycles;
		if ((champ = get_champ_by_id(n)))
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
		cursor->pos += address;
		cursor->carry = FALSE;
	}
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
