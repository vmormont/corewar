/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:19:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/27 19:28:02 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		op_fork(t_vm *vm, t_cursor *cursor)
{
	int			address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_4_bytes(vm->arena, cursor->pos + OP_SIZE) % IDX_MOD;
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	add_cursor(&vm->cursors, new_cursor);
}

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	int			address;
	t_cursor	*new_cursor;

	new_cursor = NULL;
	address = read_4_bytes(vm->arena, cursor->pos + OP_SIZE);
	if (!(new_cursor = copy_cursor(cursor, (cursor->pos + address) % MEM_SIZE)))
		ft_exit(MALLOC_FAILURE, NULL, &vm);
	add_cursor(&vm->cursors, new_cursor);
}