/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:54:39 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/21 12:44:45 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_pause(WINDOW *menu, t_bool pause)
{
	mvwaddstr(menu, 2, 3, pause ? "** PAUSED **" : "** RUNNING **");
}

static void		print_speed(WINDOW *menu, short speed)
{
	mvwprintw(menu, 4, 25, "    ");
	mvwprintw(menu, 4, 26, "%d", speed);
}

void		vis_read_keys(t_visual *vis)
{
	int			key;

	while ((key = getch()) != EOF)
	{
		if (key == 'r' || key == 'R')
			vis->vis_speed += 10;
		else if (key == 'e'|| key == 'E')
			vis->vis_speed += 1;
		else if (key == 'w' || key == 'W')
			vis->vis_speed -= 1;
		else if (key == 'q' || key == 'Q')
			vis->vis_speed -= 10;
		else if (key == 's' || key == 'S')
		{
			vis->pause = FALSE;
			nodelay(stdscr, (bool)vis->pause);
			break ;
		}
		vis->vis_speed = ft_min(1000, vis->vis_speed);
		vis->vis_speed = ft_max(1, vis->vis_speed);
		print_speed(vis->menu, vis->vis_speed);
		if (key == ' ')
		{
			vis->pause = !vis->pause;
			print_pause(vis->menu, vis->pause);
			nodelay(stdscr, (bool)!vis->pause);
			break ;
		}
		wrefresh(vis->menu);
	}
}

void		vis_cycle(t_vm *vm)
{
	show_values(vm->visual->menu, vm);
	vis_read_keys(vm->visual);
	wrefresh(vm->visual->menu);
	usleep(1000000 / vm->visual->vis_speed);
}
