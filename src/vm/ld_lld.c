/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:01:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/03 21:22:30 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static int	get_ind_value(char *arena, int index, char offset, t_bool mod)
{
	short	address;
	int		value;

	address = read_2_bytes(arena, index + offset);
	if (mod)
		address = address % IDX_MOD;
	value = read_4_bytes(arena, index + address);
	return (value);
}

void op_ld(t_vm *vm, t_cursor  *cursor)
{
	t_arg_type	type;
	int			value;
	int			num_reg;

	type = get_arg_type(vm->arena[(cursor->pos + 1) % MEM_SIZE], FIRST);
	if (type == DIR_CODE)
	{
		value = read_4_bytes(vm->arena, cursor->pos + 2);
		num_reg = vm->arena[(cursor->pos + 6) % MEM_SIZE];
	}
	else if(type == IND_CODE)
	{
		value = get_ind_value(vm->arena, cursor->pos, 2, TRUE);
		num_reg = vm->arena[(cursor->pos + 4) % MEM_SIZE];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = value;
		cursor->carry = value ? FALSE : TRUE;
	}
}

void op_lld(t_vm *vm, t_cursor  *cursor)
{
	t_arg_type	type;
	int			value;
	int			num_reg;

	type = get_arg_type(vm->arena[(cursor->pos + 1) % MEM_SIZE], FIRST);
	if (type == DIR_CODE)
	{
		value = read_4_bytes(vm->arena, cursor->pos + 2);
		num_reg = vm->arena[(cursor->pos + 6) % MEM_SIZE];
	}
	else if(type == IND_CODE)
	{
		value = get_ind_value(vm->arena, cursor->pos, 2, FALSE);
		num_reg = vm->arena[(cursor->pos + 4) % MEM_SIZE];
	}
	if (isregister(num_reg))
	{
		cursor->reg[num_reg] = value;
		cursor->carry = value ? FALSE : TRUE;
	}
}
