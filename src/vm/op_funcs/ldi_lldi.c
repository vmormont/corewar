/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:23:49 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/16 22:24:41 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	log_ldi(t_cursor *cursor, int addr1, int addr2, char reg)
{
	ft_printf("P %4d | ldi %d %d r%d\n", cursor->id, addr1, addr2, reg);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",\
	addr1, addr2, addr1 + addr2, cursor->pos + ((addr1 + addr2) % IDX_MOD));
}

static void	log_lldi(t_cursor *cursor, int addr1, int addr2, char reg)
{
	ft_printf("P %4d | %s %d %d r%d\n", cursor->id,\
	cursor->op_code == LDI ? "ldi" : "lldi", addr1, addr2, reg);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",\
	addr1, addr2, addr1 + addr2, cursor->pos + addr1 + addr2);
}

void 		op_ldi(t_vm *vm, t_cursor *cursor)
{
	int		code_arg;
	int		arg1;
	int		arg2;
	char	reg;
	char	offset;

	offset = 2;
	code_arg = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	arg1 = get_arg_value(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	arg2 = get_arg_value(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(reg) && cursor->exec)
	{
		cursor->reg[reg] = read_4_bytes(vm->arena,\
		cursor->pos + ((arg1 + arg2) % IDX_MOD));
		if (vm->options.verbos == V_OPERATIONS)
			log_ldi(cursor, arg1, arg2, reg);
	}
}

void 		op_lldi(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		arg1;
	int		arg2;
	char	reg;
	char	offset;

	offset = 2;
	code_arg = vm->arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
	arg1 = get_arg_value(vm->arena, cursor, (code_arg >> 6) & 3, &offset);
	arg2 = get_arg_value(vm->arena, cursor, (code_arg >> 4) & 3, &offset);
	reg = vm->arena[(cursor->pos + offset) % MEM_SIZE];
	if (isregister(reg) && cursor->exec)
	{
		cursor->reg[reg] = read_4_bytes(vm->arena, cursor->pos + arg1 + arg2);
		cursor->carry = cursor->reg[reg] ? FALSE : TRUE;
		if (vm->options.verbos == V_OPERATIONS)
			log_lldi(cursor, arg1, arg2, reg);
	}
}
