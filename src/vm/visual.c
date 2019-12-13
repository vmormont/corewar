/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/13 17:58:07 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void 	print_frame(WINDOW *win)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	move(50, 50);
	attron(COLOR_PAIR(1));
	addch('C');
}

static void		print_info(t_vm *vm)
{
	int		i;

	mvaddstr(5, (3 * DUMP_COLUMNS) + 5, "Cycles/second limit : ");
	mvaddstr(8, (3 * DUMP_COLUMNS) + 5, "Cycle : ");
	mvaddstr(14, (3 * DUMP_COLUMNS) + 5, "Processes : ");
	i = -1;
	/*информация про игроков;
	while (++i < vm->num_of_champs)
		print_champ_info(vm->champs);*/
	mvaddstr(20, (3 * DUMP_COLUMNS) + 5, "CYCLE TO DIE : ");
	mvaddstr(22, (3 * DUMP_COLUMNS) + 5, "CYCLE DELTA : ");
	mvaddstr(24, (3 * DUMP_COLUMNS) + 5, "NBR LIVE : ");
	mvaddstr(26, (3 * DUMP_COLUMNS) + 5, "MAX CHECKS : ");

	refresh();
	getch();
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
