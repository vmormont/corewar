/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/19 00:31:57 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_visual *new_visual()
{
	t_visual *visual;

	if (!(visual = (t_visual*)malloc(sizeof(t_visual))))
		return (NULL);
	ft_bzero((void*)visual, sizeof(t_visual));
	visual->vis_speed = 50;
	visual->pause = TRUE;
	return (visual);
}

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

void		visualizator(t_vm *vm)
{
	if (!(vm->visual = new_visual()))
		ft_exit(MALLOC_FAILURE, &vm);
	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);

	//инициализируем цвета
	color_init();
	//убираем курсор
	curs_set(NONE);
	//печатаем рамку
	print_frame();

	//создаем окно меню
	vm->visual->menu = newwin(DUMP_ROWS + 2, 69, 2, (DUMP_COLUMNS * 3) + 5);
	//печатаем информацию о чемпионах в окно меню
	print_info(vm->visual->menu, vm);

	//тут надо создать окно арены
	print_src_arena(vm, vm->arena);

	noecho();
	getch();
	wclear(vm->visual->menu);
	refresh();
	wrefresh(vm->visual->menu);
	getch();
}
