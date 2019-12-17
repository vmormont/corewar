/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/17 20:31:28 by pcredibl         ###   ########.fr       */
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

void	show_values(t_vm *vm)
{
	mvprintw(5, (3 * DUMP_COLUMNS) + 31, "%d", vm->vis_speed);
	mvprintw(8, (3 * DUMP_COLUMNS) + 17, "%d", vm->cycles);
	mvprintw(11, (3 * DUMP_COLUMNS) + 21, "%d", vm->num_of_cursors);
	refresh();
}

void		print_info(t_vm *vm)
{
	attron(A_BOLD);
	mvaddstr(3, (3 * DUMP_COLUMNS) + 8, vm->pause ? "** PAUSED **" : "** RUNNING **");
	mvaddstr(5, (3 * DUMP_COLUMNS) + 8, "Cycles/second limit : ");
	mvaddstr(8, (3 * DUMP_COLUMNS) + 8, "Cycle : ");
	mvaddstr(11, (3 * DUMP_COLUMNS) + 8, "Processes : ");
	print_champ_info(vm, vm->champs);
	mvprintw(11 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"CYCLE TO DIE :\t%d", vm->cycles_to_die);
	mvprintw(13 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"CYCLE DELTA :\t%d", CYCLE_DELTA);
	mvprintw(15 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"NBR LIVE :\t%d", NBR_LIVE);
	mvprintw(17 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"MAX CHECKS :\t%d", MAX_CHECKS);
	refresh();
	attron(A_NORMAL);
}

static void		print_champ_code(int *i, int *j, t_champ *champ, t_vm *vm)
{
	int			counter;
	static char	color_code = 0;
	char		*arena;		
	
	counter = 0;
	arena = vm->arena;
	color_code ++;
	color_set(color_code, NULL);
	while (counter < champ->code_size)
	{
		cursor_in_pos(vm->cursors_pos, (*i) * DUMP_COLUMNS + (*j)) ? color_set(color_code + 5, NULL) : 0;
		mvprintw((*i) + 3, (3 * (*j)) + 3, "%02hhx", arena[(*i) * DUMP_COLUMNS + (*j)]);
		cursor_in_pos(vm->cursors_pos, (*i) * DUMP_COLUMNS + (*j)) ? color_set(color_code, NULL) : 0;
		(*j)++;
		if (!((*j) % DUMP_COLUMNS))
		{
			(*j) = 0;
			(*i)++;
		}
		counter++;
	}
	color_set(WHITE_TEXT, NULL);
}

void		print_src_arena(t_vm *vm, char *arena)
{
	int		i;
	int		j;
	t_champ	*temp;
	//char	color_code;

	//color_code = 0;
	temp = vm->champs;
	attron(A_NORMAL);
	i = 0;
	while (i < DUMP_ROWS)
	{
		j = 0;
		while (j < DUMP_COLUMNS)
		{
			if (!(((i * DUMP_COLUMNS) + j) % (((DUMP_COLUMNS * DUMP_ROWS)\
			/ vm->num_of_champs))) && temp)
			{
				//color_code++;
				//color_set(color_code, NULL);
				print_champ_code(&i, &j, temp, vm);
				temp = temp->next;
			}
			cursor_in_pos(vm->cursors_pos, i * DUMP_COLUMNS + j) ? color_set(FRAME, NULL) : 0;
			mvprintw(i + 3, (3 * j) + 3, "%02d", 0);
			cursor_in_pos(vm->cursors_pos, i * DUMP_COLUMNS + j) ? color_set(WHITE_TEXT, NULL) : 0;
			j++;
		}
		i++;
	}
	refresh();
}