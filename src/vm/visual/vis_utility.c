/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/19 23:48:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_visual 		*new_visual(void)
{
	t_visual *visual;

	if (!(visual = (t_visual*)malloc(sizeof(t_visual))))
		return (NULL);
	ft_bzero((void*)visual, sizeof(t_visual));
	visual->vis_speed = 500;
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

void			show_values(WINDOW *menu, t_vm *vm)
{
	mvwprintw(menu, 4, 26, "%d", vm->visual->vis_speed);
	mvwprintw(menu, 7, 12, "%d", vm->cycles);
	mvwprintw(menu, 10, 16, "%d", vm->num_of_cursors);
	wrefresh(menu);

	//делаем задержку чтобы в секунду успевало сделаться
	//заданное количество циклов
	usleep(1000000 / vm->visual->vis_speed);
//	getch();
}
