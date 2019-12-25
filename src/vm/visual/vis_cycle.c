/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:54:39 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/25 12:26:03 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_pause(WINDOW *menu, t_bool pause)
{
	mvwaddstr(menu, 2, 3, pause ? "** PAUSED **" : "** RUNNING **");
}

static void		process_keys(t_visual *vis, int key)
{
	if (key == 'r' || key == 'R')
		vis->vis_speed += 10;
	else if (key == 'e' || key == 'E')
		vis->vis_speed += 1;
	else if (key == 'w' || key == 'W')
		vis->vis_speed -= 1;
	else if (key == 'q' || key == 'Q')
		vis->vis_speed -= 10;
	else if (key == 'p' || key == 'P')
		vis_sound(vis);
}

static t_bool	read_keys(t_visual *vis, int key)
{
	process_keys(vis, key);
	if (key == 's' || key == 'S')
	{
		vis->pause = FALSE;
		nodelay(stdscr, (bool)vis->pause);
		return (FALSE);
	}
	vis->vis_speed = ft_min(VIS_MAX_SPEED, vis->vis_speed);
	vis->vis_speed = ft_max(VIS_MIN_SPEED, vis->vis_speed);
	mvwprintw(vis->menu, 4, 26, "%-5d", vis->vis_speed);
	if (key == ' ')
	{
		vis->pause = !vis->pause;
		print_pause(vis->menu, vis->pause);
		nodelay(stdscr, (bool)!vis->pause);
		return (FALSE);
	}
	return (TRUE);
}

void			vis_cycle(t_vm *vm)
{
	int key;

	show_values(vm->visual->menu, vm);
	while ((key = getch()) != EOF)
	{
		if (!read_keys(vm->visual, key))
			break ;
		wrefresh(vm->visual->menu);
	}
	wrefresh(vm->visual->menu);
	check_attr(vm);
	wrefresh(vm->visual->arena);
	usleep(VIS_SPEED_DEL / vm->visual->vis_speed);
}
