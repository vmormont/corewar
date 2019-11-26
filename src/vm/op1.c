/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:01:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/26 15:22:33 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void op_ld(t_vm *vm, t_cursor  *cursor)
{
	int		code_arg;
	int		num;
	int		num_reg;
	
	code_arg = vm->arena[cursor->pos + 1];
	ft_printf("cursor pos = %d\n", cursor->pos);
	if (((code_arg >> 6) & 3) == T_DIR)
	{
		num = read_4_bytes(vm->arena, cursor->pos + 2);
		num_reg = vm->arena[cursor->pos + 6];
		ft_printf("num = %d,   num_reg = %d\n", num, num_reg);
		if (num_reg > 0 && num_reg < 17)
			cursor->reg[num_reg] = num;
	}
}