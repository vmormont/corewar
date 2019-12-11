/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/11 17:04:22 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_info(t_vm *vm)
{
	move(3, (2 * DUMP_COLUMNS) + 5);
	printw("*PLAY*");
	move(4, (2 * DUMP_COLUMNS) + 5);
	printw("row 2");
	refresh();
	getch();
	clear();
	printw("screen 2\n");
	refresh();
}

void	visualizator(t_vm *vm)
{
	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	print_info(vm);
	getch();
	
}
