/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 16:55:46 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_frame()
{
	int		i;

	color_set (FRAME, NULL);
	i = 0;
	while (++i < ARENA_WIDTH + 75)
	{
		mvaddch(1, i, ' ');
		mvaddch(ARENA_HEIGHT + 4, i, ' ');
	}
	i = 0;
	while (++i < ARENA_HEIGHT + 5)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, ARENA_WIDTH + 4, ' ');
		mvaddch(i, ARENA_WIDTH + 75, ' ');
	}
	color_set (WHITE_TEXT, NULL);
}

static void		color_init(void)
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
	init_pair(RED_LIVE, COLOR_RED, COLOR_WHITE);
	init_pair(GREEN_LIVE, COLOR_GREEN, COLOR_WHITE);
	init_pair(BLUE_LIVE, COLOR_BLUE, COLOR_WHITE);
	init_pair(YELLOW_LIVE, COLOR_YELLOW, COLOR_WHITE);
}

static void		print_champs(WINDOW *menu, t_vm *vm, t_champ *champs)
{
	int		i;

	i = 0;
	while (i < vm->num_of_champs)
	{
		mvwprintw(menu, 12 + (i * 4), 3, "Player %d : ", champs->id);
		wcolor_set(menu, i + 1, NULL);
		wprintw(menu, "%s\n", champs->name);
		wcolor_set(menu, WHITE_TEXT, NULL);
		mvwprintw(menu, 13 + (i * 4), 5, "Last live :", champs->last_live);
		mvwprintw(menu, 14 + (i * 4), 5, "Lives in current period :",\
		champs->lives_in_period);
		i++;
		champs = champs->next;
	}
}

static void		print_info(WINDOW *menu, t_vm *vm)
{
	wattron(menu, A_BOLD);
	mvwaddstr(menu, 2, 3, "** PAUSED **");
	mvwaddstr(menu, 4, 3, "Cycles/second limit : ");
	mvwaddstr(menu, 7, 3, "Cycle : ");
	mvwaddstr(menu, 10, 3, "Processes : ");
	mvwprintw(menu, 16 + (4 * vm->num_of_champs) + 3, 3,\
	"CYCLE DELTA :\t%d", CYCLE_DELTA);
	mvwprintw(menu, 18 + (4 * vm->num_of_champs) + 3, 3,\
	"NBR LIVE :\t\t%d", NBR_LIVE);
	mvwprintw(menu, 20 + (4 * vm->num_of_champs) + 3, 3,\
	"MAX CHECKS :\t\t%d", MAX_CHECKS);
	mvwprintw(menu, 12 + (4 * vm->num_of_champs) + 3, 3,\
	"LIVE OPERATION IN CURRENT PERIOD : ", vm->num_live_op);
	mvwprintw(menu, 14 + (4 * vm->num_of_champs) + 3, 3,\
	"CYCLE TO DIE : ", vm->cycles_to_die);
	show_values(menu, vm);
}

void			visualizator(t_vm *vm)
{
	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	//инициализируем цвета
	color_init();
	//убираем курсор
	curs_set(NONE);
	noecho();
	//печатаем рамку
	print_frame();
	refresh();
	//создаем окно меню
	if (!(vm->visual->menu = newwin(ARENA_HEIGHT + 2, 69, 2, ARENA_WIDTH + 5)))
		ft_exit(MALLOC_FAILURE, &vm);
	//печатаем информацию о чемпионах в окно меню
	print_info(vm->visual->menu, vm);
	print_champs(vm->visual->menu, vm, vm->champs);
	wrefresh(vm->visual->menu);
	//создаем окно арены
	if (!(vm->visual->arena = newwin(ARENA_HEIGHT, ARENA_WIDTH, 3, 3)))
		ft_exit(MALLOC_FAILURE, &vm);
	print_arena(vm);
}
