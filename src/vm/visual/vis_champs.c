/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_champs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:05:15 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 22:54:23 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_champ_code(int *i, int *j, t_champ *champ, t_vm *vm)
{
	int			counter;
	char		*arena;

	counter = 0;
	arena = vm->arena;
	wcolor_set(vm->visual->arena, ft_abs(champ->id), NULL);
	while (counter < champ->code_size)
	{
		if (vm->options.terminal != 2)
			mvwprintw(vm->visual->arena, (*i), (3 * (*j)), "%02hhx",\
			arena[(*i) * DUMP_COLUMNS + (*j)]);
		else
			mvwprintw(vm->visual->arena, (*i), (3 * (*j)), "ff");
		(*j)++;
		if (!((*j) % DUMP_COLUMNS))
		{
			(*j) = 0;
			(*i)++;
		}
		counter++;
	}
	set_cursor(vm, (*i) * DUMP_COLUMNS + (*j) - counter);
	wcolor_set(vm->visual->arena, WHITE_TEXT, NULL);
}

void		print_arena(t_vm *vm)
{
	int		i;
	int		j;
	char	byte;
	t_champ	*temp;

	temp = vm->champs;
	byte = vm->options.terminal == NORMAL_MODE ? 0 : 0xFF;
	wattron(vm->visual->arena, A_NORMAL);
	i = 0;
	while (i < DUMP_ROWS)
	{
		j = 0;
		while (j < DUMP_COLUMNS)
		{
			if (!(((i * DUMP_ROWS) + j) % (MEM_SIZE / vm->num_of_champs)) && temp)
			{
				print_champ_code(&i, &j, temp, vm);
				temp = temp->next;
				continue;
			}
			mvwprintw(vm->visual->arena, i, (VIS_BYTE_SIZE * j), "%02x", byte);
			j++;
		}
		i++;
	}
	wrefresh(vm->visual->arena);
}
