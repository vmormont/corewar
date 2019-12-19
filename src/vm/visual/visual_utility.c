/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/19 18:49:14 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void color_init(void)
{
	start_color();
	init_pair(RED_TEXT, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN_TEXT, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE_TEXT, COLOR_BLUE, COLOR_BLACK);
	init_pair(YELLOW_TEXT, COLOR_YELLOW, COLOR_BLACK);
	init_pair(WHITE_TEXT, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(BLUE_CURSOR, COLOR_BLACK, COLOR_BLUE);
	init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(FRAME, COLOR_BLACK, COLOR_WHITE);
}

void	show_values(WINDOW *menu, t_vm *vm)
{
	mvwprintw(menu, 4, 26, "%d", vm->visual->vis_speed);
	mvwprintw(menu, 7, 12, "%d", vm->cycles);
	mvwprintw(menu, 10, 16, "%d", vm->num_of_cursors);
	wrefresh(menu);
}

void		print_info(WINDOW *menu, t_vm *vm)
{
	wattron(menu, A_BOLD);
	mvwaddstr(menu, 2, 3, vm->visual->pause ? "** PAUSED **" : "** RUNNING **");
	mvwaddstr(menu, 4, 3, "Cycles/second limit : ");
	mvwaddstr(menu, 7, 3, "Cycle : ");
	mvwaddstr(menu, 10, 3, "Processes : ");
	print_champ_info(menu, vm, vm->champs);
	mvwprintw(menu, 12 + (4 * vm->num_of_champs) + 7, 3,\
	"CYCLE TO DIE :\t%d", vm->cycles_to_die);
	mvwprintw(menu, 14 + (4 * vm->num_of_champs) + 7, 3,\
	"CYCLE DELTA :\t%d", CYCLE_DELTA);
	mvwprintw(menu, 16 + (4 * vm->num_of_champs) + 7, 3,\
	"NBR LIVE :\t\t%d", NBR_LIVE);
	mvwprintw(menu, 18 + (4 * vm->num_of_champs) + 7, 3,\
	"MAX CHECKS :\t\t%d", MAX_CHECKS);
	show_values(menu, vm);
}

static void		print_champ_code(int *i, int *j, t_champ *champ, t_vm *vm)
{
	int			counter;
	static char	color_code = 0;
	char		*arena;

	counter = 0;
	arena = vm->arena;
	color_code ++;
	wcolor_set(vm->visual->arena, color_code, NULL);
	while (counter < champ->code_size)
	{
		cursor_in_pos(vm->visual->cursors_pos, (*i) * DUMP_COLUMNS + (*j)) ?\
		wcolor_set(vm->visual->arena, color_code + 5, NULL) : 0;
		if (vm->options.terminal != 2)
			mvwprintw(vm->visual->arena, (*i), (3 * (*j)), "%02hhx",\
			arena[(*i) * DUMP_COLUMNS + (*j)]);
		else
			mvwprintw(vm->visual->arena, (*i), (3 * (*j)), "ff");
		cursor_in_pos(vm->visual->cursors_pos, (*i) * DUMP_COLUMNS + (*j)) ?\
		wcolor_set(vm->visual->arena, color_code, NULL) : 0;
		(*j)++;
		if (!((*j) % DUMP_COLUMNS))
		{
			(*j) = 0;
			(*i)++;
		}
		counter++;
	}
	wcolor_set(vm->visual->arena, WHITE_TEXT, NULL);
}

void		print_src_arena(t_vm *vm, char *arena)
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
			if (!(((i * DUMP_COLUMNS) + j) % (((DUMP_COLUMNS * DUMP_ROWS)\
			/ vm->num_of_champs))) && temp)
			{
				print_champ_code(&i, &j, temp, vm);
				temp = temp->next;
			}
			cursor_in_pos(vm->visual->cursors_pos, i * DUMP_COLUMNS + j) ?\
			wcolor_set(vm->visual->arena, FRAME, NULL) : 0;
			vm->options.terminal == 2 ? mvwprintw(vm->visual->arena, i, (3 * j), "ff") :\
			mvwprintw(vm->visual->arena, i, (3 * j), "%02d", 0);
			cursor_in_pos(vm->visual->cursors_pos, i * DUMP_COLUMNS + j) ?\
			wcolor_set(vm->visual->arena, WHITE_TEXT, NULL) : 0;
			j++;
		}
		i++;
	}
	wrefresh(vm->visual->arena);
}

void		destroy_vis(t_visual **vis)
{
	delwin((*vis)->arena);
	delwin((*vis)->menu);
	//ft_memdel((void**)&vis);
	free(*vis);
}
