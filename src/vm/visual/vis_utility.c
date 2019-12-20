/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/20 14:25:35 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_visual 		*new_visual(void)
{
	t_visual *visual;

	if (!(visual = (t_visual*)malloc(sizeof(t_visual))))
		return (NULL);
	ft_bzero((void*)visual, sizeof(t_visual));
	visual->vis_speed = 100;
	visual->pause = TRUE;
	return (visual);
}

void			destroy_visual(t_visual **vis)
{
	if (vis && *vis)
	{
		delwin((*vis)->arena);
		delwin((*vis)->menu);
		endwin();
		free(*vis);
		*vis = NULL;
	}
}

t_bool			cursor_in_pos(int *cursors_map, int pos)
{
	if (cursors_map[pos])
		return (TRUE);
	else
		return (FALSE);
}

void			clear_values(t_vm *vm)
{
	mvwprintw(vm->visual->menu, 4, 26, "                    ");
	mvwprintw(vm->visual->menu, 7, 12, "                    ");
	mvwprintw(vm->visual->menu, 10, 16, "                    ");
	mvwprintw(vm->visual->menu, 12 + (4 * vm->num_of_champs) + 3, 3,\
	"LIVE OPERATION IN CURRENT PERIOD :\t%s", "                    ");
	mvwprintw(vm->visual->menu, 14 + (4 * vm->num_of_champs) + 3, 3,\
	"CYCLE TO DIE :\t%s", "                    ");
	wrefresh(vm->visual->menu);	
}

void			show_values(WINDOW *menu, t_vm *vm)
{
	//clear_value(vm);
	print_champ_info(menu, vm, vm->champs);
	mvwprintw(menu, 4, 26, "%d", vm->visual->vis_speed);
	mvwprintw(menu, 7, 12, "%d", vm->cycles);
	mvwprintw(menu, 10, 16, "%d", vm->num_of_cursors);
	mvwprintw(menu, 12 + (4 * vm->num_of_champs) + 3, 3,\
	"LIVE OPERATION IN CURRENT PERIOD :\t%d", vm->num_live_op);
	mvwprintw(menu, 14 + (4 * vm->num_of_champs) + 3, 3,\
	"CYCLE TO DIE :\t%d", vm->cycles_to_die);
	wrefresh(menu);

	//делаем задержку чтобы в секунду успевало сделаться
	//заданное количество циклов
	//usleep(1000000 / vm->visual->vis_speed);
//	getch();
}
