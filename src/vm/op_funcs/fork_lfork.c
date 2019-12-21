/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:19:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/20 18:39:55 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op		g_op_tab[];

void		op_fork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	cursor->step = 3;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (!(new_cursor = copy_cursor(cursor,\
	(cursor->pos + (address % IDX_MOD)) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, &vm);
	add_cursor(&vm->cursors, new_cursor);
	vm->num_of_cursors += 1;
	if (vm->visual)
		set_cursor(vm, new_cursor->pos, ft_abs(new_cursor->champ->id));
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | fork %d (%d)\n", cursor->id, address,\
		new_cursor->pos);
}

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	short		address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	cursor->step = 3;
	address = read_2_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, &vm);
	add_cursor(&vm->cursors, new_cursor);
	vm->num_of_cursors += 1;
	if (vm->visual)
		set_cursor(vm, new_cursor->pos, ft_abs(new_cursor->champ->id));
	if (vm->options.verbos == V_OPERATIONS)
		ft_printf("P %4d | lfork %d (%d)\n", cursor->id, address,\
		cursor->pos + address);
}
