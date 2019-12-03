/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:19:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/03 17:53:22 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



void		op_fork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE) % IDX_MOD;
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	new_cursor->op_code = vm->arena[new_cursor->pos];
	add_cursor(&vm->cursors, new_cursor);
	//ft_printf("op code = %d, 1: 10, 2: 0, 3: 0, step = %d\n", cursor->op_code,\
	cursor->step);
}

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	new_cursor->op_code = vm->arena[new_cursor->pos];
	add_cursor(&vm->cursors, new_cursor);
	//ft_printf("op code = %d, 1: 10, 2: 0, 3: 0, step = %d\n", cursor->op_code,\
	cursor->step);
}
