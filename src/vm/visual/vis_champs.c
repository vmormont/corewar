/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_champs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:05:15 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/24 14:15:40 by pcredibl         ###   ########.fr       */
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
		if (vm->options.terminal != STEALTH_MODE)
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

static void	fill_arena_by_zero(WINDOW *arena, char opt, int i, int j)
{
	opt == STEALTH_MODE ? mvwprintw(arena, i, (3 * j), "ff") \
	: mvwprintw(arena, i, (3 * j), "%02d", 0);
}

void		print_arena(t_vm *vm)
{
	int		i;
	int		j;
	t_champ	*temp;

	temp = vm->champs;
	wattron(vm->visual->arena, A_NORMAL);
	i = 0;
	while (i < DUMP_ROWS)
	{
		j = 0;
		while (j < DUMP_COLUMNS)
		{
			if (!(((i * DUMP_ROWS) + j) % (MEM_SIZE / vm->num_of_champs))\
			&& temp)
			{
				print_champ_code(&i, &j, temp, vm);
				temp = temp->next;
				continue;
			}
			fill_arena_by_zero(vm->visual->arena, vm->options.terminal, i, j);
			j++;
		}
		i++;
	}
	wrefresh(vm->visual->arena);
}
