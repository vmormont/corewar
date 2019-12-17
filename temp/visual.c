/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/17 18:19:03 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void 	print_frame()
{
	int		i;

	color_set (FRAME, NULL);
	i = 0;
	while (++i < (3 * DUMP_COLUMNS) + 75)
	{
		mvaddch(1, i, ' ');
		mvaddch(DUMP_ROWS + 4, i, ' ');
	}
	i = 0;
	while (++i < DUMP_ROWS + 5)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, (3 * DUMP_COLUMNS) + 4, ' ');
		mvaddch(i, (3 * DUMP_COLUMNS) + 75, ' ');
	}
	color_set (WHITE_TEXT, NULL);
}

static void		print_src_arena(t_vm *vm, char *byte)
{
	int		i;
	int		j;
	t_champ	*temp;
	char	color_code;
	int		champ_begin;

	color_code = 0;
	temp = vm->champs;
	attron(A_BOLD);
	i = 0;
	while (i < DUMP_ROWS)
	{
		j = 0;

		while (j < DUMP_COLUMNS)
		{
			//mvprintw(i + 3, 270, "STR");
			//move(i + 3, (3 * j) + 3);
			if (!(((i * DUMP_COLUMNS) + j) % (((DUMP_COLUMNS * DUMP_ROWS)\
			/ vm->num_of_champs))) && temp)
			{
				color_code++;
				//mvprintw(color_code, 270, "color code = %d", color_code);
				color_set(color_code, NULL);
				champ_begin = (i * DUMP_COLUMNS) + j;
				//mvprintw(j + 3, 300, "code size = %d", temp->code_size);
			}
			else if (temp && (((i * DUMP_COLUMNS) + j) - champ_begin) == temp->code_size)
			{
				color_set(WHITE_TEXT, NULL);
				champ_begin = 0;
				temp = temp->next;
				//mvprintw(i, 300, "code size = %d", temp->code_size);
			}
			mvprintw(i + 3, (3 * j) + 3, "%02hhx ", *byte);
			byte += 1;
			j++;
		}
		i++;
	}
	refresh();

}

static void		print_champ_info(t_vm *vm, t_champ *champs)
{
	int		i;

	i = 0;
	while (i < vm->num_of_champs)
	{
		mvprintw(16 + (i * 4), (3 * DUMP_COLUMNS) + 8, "Player %d : ", champs->id);
		color_set(i + 1, NULL);
		printw("%s\n", champs->name);
		color_set(WHITE_TEXT, NULL);
		mvprintw(17 + (i * 4), (3 * DUMP_COLUMNS) + 10,\
		"Last live :\t\t\t%d\n", champs->last_live);
		mvprintw(18 + (i * 4), (3 * DUMP_COLUMNS) + 10,\
		"Lives in current period :\t%d\n", champs->lives_in_period);
		i++;
		champs = champs->next;
	}
	refresh();
}

static void		print_info(t_vm *vm)
{
	attron(A_BOLD);
	mvaddstr(3, (3* DUMP_COLUMNS) + 8, vm->pause ? "** PAUSED **" : "** RUNNING **");
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

static void	show_values(t_vm *vm)
{
	mvprintw(5, (3 * DUMP_COLUMNS) + 31, "%d", vm->vis_speed);
	mvprintw(8, (3 * DUMP_COLUMNS) + 17, "%d", vm->cycles);
	mvprintw(11, (3 * DUMP_COLUMNS) + 21, "%d", vm->num_of_cursors);
	refresh();
}

static void color_init(void)
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

void	visualizator(t_vm *vm)
{
	WINDOW *exp;
	WINDOW *arena;

	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	//arena = newwin(DUMP_ROWS, 3 * DUMP_COLUMNS, 3, 3);
	color_init();
	//box(arena, 0, 0);
	print_src_arena(vm, vm->arena);
	print_info(vm);
	show_values(vm);
	print_frame();
	noecho();
	getch();
}
