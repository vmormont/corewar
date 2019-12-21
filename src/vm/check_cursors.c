/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cursors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 14:46:18 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/21 17:37:03 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_bool	time_to_kill(t_vm *vm, t_cursor *cursor)
{
	if (((vm->cycles - cursor->cycle_live) >= vm->cycles_to_die)\
	|| vm->cycles_to_die <= 0)
		return (TRUE);
	return (FALSE);
}

static void		one_shot(t_vm *vm, t_cursor *temp)
{
	if (vm->options.verbos == V_DEATHS)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",\
		temp->id, vm->cycles - temp->cycle_live, vm->cycles_to_die);
	}
	if (vm->visual)
	{
		vm->visual->cursors_pos[temp->pos] -= 1;
		if (!vm->visual->cursors_pos[temp->pos])
			clear_cursor(vm, temp->pos);
	}
	vm->num_of_cursors -= 1;
	ft_memdel((void**)&temp);
}

static void		kill_first_cursors(t_vm *vm)
{
	t_cursor *cursor;
	t_cursor *temp;

	cursor = vm->cursors;
	while (cursor && time_to_kill(vm, cursor))
	{
		temp = cursor;
		cursor = cursor->next;
		one_shot(vm, temp);
	}
	vm->cursors = cursor;
}

void			check_cursors(t_vm *vm)
{
	t_cursor	*first;
	t_cursor	*second;
	t_cursor	*temp;

	vm->cycles_from_last_check = 0;
	if (vm->cursors)
	{
		kill_first_cursors(vm);
		first = vm->cursors;
		while (first)
		{
			if (time_to_kill(vm, first))
			{
				temp = first;
				first = first->next;
				second->next = first;
				one_shot(vm, temp);
				continue;
			}
			second = first;
			first = first->next;
		}
	}
}
