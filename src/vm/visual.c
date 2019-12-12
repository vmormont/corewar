/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/12 18:34:44 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void 	print_frame(WINDOW *win)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	attron(1);
}

static void		print_info(t_vm *vm)
{
	int		i;

	i = 0;
	while (++i < 10)
	{
		clear();
		move(i, (2 * DUMP_COLUMNS) + 5);
		printw("*PLAY*");
		usleep(100000);
		refresh();
	}
	getch();
	move(i - 1, (2 * DUMP_COLUMNS) + 5);
	printw("123456\n");
	refresh();
}

void	visualizator(t_vm *vm)
{
	//WINDOW *main_window;
	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	print_info(vm);
	//print_frame();
	getch();
	
}
