/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/18 17:57:56 by pcredibl         ###   ########.fr       */
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

void		print_champ_info(WINDOW *menu, t_vm *vm, t_champ *champs)
{
	int		i;

	i = 0;
	while (i < vm->num_of_champs)
	{
		mvwprintw(menu, 12 + (i * 4), 3, "Player %d : ", champs->id);
		wcolor_set(menu, i + 1, NULL);
		wprintw(menu, "%s\n", champs->name);
		wcolor_set(menu, WHITE_TEXT, NULL);
		mvwprintw(menu, 13 + (i * 4), 5, "Last live :\t\t%d\n",\
		champs->last_live);
		mvwprintw(menu, 14 + (i * 4), 5, "Lives in current period :\t%d\n",\
		champs->lives_in_period);
		i++;
		champs = champs->next;
	}
	refresh();
}

void	visualizator(t_vm *vm)
{
	WINDOW *exp;
	WINDOW *menu;

	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	//arena = newwin(DUMP_ROWS, 3 * DUMP_COLUMNS, 3, 3);
	color_init();
	//box(arena, 0, 0);
	menu = newwin(DUMP_ROWS + 2, 69, 2, (DUMP_COLUMNS * 3) + 5);
	print_src_arena(vm, vm->arena);
	print_frame();
	print_info(menu, vm);
	noecho();
	getch();
	wclear(menu);
	wrefresh(menu);
	getch();
	//wclear(arena);
	//wrefresh(arena);
	//print_src_arena(vm, vm->arena);


















































































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
