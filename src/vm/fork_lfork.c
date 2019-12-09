/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:19:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/09 13:20:51 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op		g_op_tab[];

void		op_fork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE) % IDX_MOD;
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	new_cursor->op_code = vm->arena[new_cursor->pos % MEM_SIZE];
	if (new_cursor->op_code > 0 && new_cursor->op_code <= 16)
		new_cursor->cycles2go = g_op_tab[new_cursor->op_code].cycles2go;
	else
		new_cursor->cycles2go = 1;
	add_cursor(&vm->cursors, new_cursor);
	//print_reg(cursor->reg);
	//print_reg(new_cursor->reg);
	//ft_printf("---------------------------------------------------------------------\n");
//	ft_printf("[%d] fork pos = %d, new_pos = %d\n", vm->cycles, cursor->pos, new_cursor->pos);
}

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	new_cursor->op_code = vm->arena[new_cursor->pos % MEM_SIZE];
	if (new_cursor->op_code > 0 && new_cursor->op_code <= 16)
		new_cursor->cycles2go = g_op_tab[new_cursor->op_code].cycles2go;
	else
		new_cursor->cycles2go = 1;
	add_cursor(&vm->cursors, new_cursor);
	//print_reg(cursor->reg);
	//print_reg(new_cursor->reg);
	//ft_printf("---------------------------------------------------------------------\n");
//	ft_printf("[%d] lfork pos = %d, new_pos = %d\n", vm->cycles, cursor->pos, new_cursor->pos);
}
