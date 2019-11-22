/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 21:16:42 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

static void	define_step_and_time_cursor(t_cursor *cursor, char code_arg)
{
	char	tdir_size;
	char	i;
	char	arg;

	tdir_size = g_op_tab[cursor->op_code].tdir_size ? 2 : 4;
	i = 6;
	while (i)
	{
		arg = (code_arg >> i) & 3;

	}

}

static void	move_and_read_cursor(t_cursor *cursor, char *arena)
{
	char	code_arg;

	cursor->pos += cursor->step;
	ft_memcpy(cursor->op_code, (const void*)&(arena[cursor->pos]), 1);
	if(!(cursor->op_code > 0 && cursor->op_code < 17))
	{
		cursor->step = 1;
		cursor->time_to_exec = 0;
	}
	else
	{
		if (g_op_tab[cursor->op_code].code_args)
		{
			cursor->pos += 4;
			code_arg = arena[cursor->pos];
			define_step_cursor(cursor, code_arg);
		}
		else
			cursor->step = 3;
		cursor->time_to_exec = g_op_tab[cursor->op_code].cycles2go;	
	}
	

}

void	cycle(t_vm *vm)
{
	t_cursor	*tmp;

	tmp = vm->cursors;
	while (tmp)
	{
		tmp->time_to_exec -= 1;
		if (!tmp->time_to_exec)
			exec_op(tmp);
		if (tmp->time_to_exec == -1)
			move_and_read_cursor(tmp, vm->arena);		
		tmp = tmp->next;
	}
	vm->cycles += 1;
	while ()
}