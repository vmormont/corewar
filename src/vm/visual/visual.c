/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/17 20:22:33 by pcredibl         ###   ########.fr       */
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

char		cursor_in_pos(int *cursors_map, int pos)
{
	if (cursors_map[pos])
		return (1);
	else
		return (0);
}

void		print_champ_info(t_vm *vm, t_champ *champs)
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
	//wclear(arena);
	//wrefresh(arena);
	getch();
	//print_src_arena(vm, vm->arena);
	getch();
	/*exp = newwin(30, 75, 5, (3 * DUMP_COLUMNS) + 80);
	//box(exp, 1, 1);
	wattron(exp, A_BOLD);
	//wcolor_set(exp, 2, NULL);
	mvwaddstr(exp, 0, 1, "hello");
	mvwaddstr(exp, 1, 1, "world");
	wrefresh(exp);*/
	/*getch();
	wclear(exp);
	wrefresh(exp);
	getch();*/
}
