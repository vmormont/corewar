/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/21 12:49:46 by astripeb         ###   ########.fr       */
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

static void		print_champ_info(WINDOW *menu, t_vm *vm, t_champ *champs)
{
	int		i;

	i = 0;
	wcolor_set(menu, WHITE_TEXT, NULL);
	while (i < vm->num_of_champs)
	{
		mvwprintw(menu, 13 + (i * 4), 35, "%d     ", champs->last_live);
		mvwprintw(menu, 14 + (i * 4), 35, "%d     ", champs->lives_in_period);
		i++;
		champs = champs->next;
	}
}

void			show_values(WINDOW *menu, t_vm *vm)
{
	print_champ_info(menu, vm, vm->champs);
	mvwprintw(menu, 4, 26, "%d      ", vm->visual->vis_speed);
	mvwprintw(menu, 7, 12, "%d      ", vm->cycles);
	mvwprintw(menu, 10, 16, "%d     ", vm->num_of_cursors);
	mvwprintw(menu, 15 + (4 * vm->num_of_champs), 40, "%d     ",\
	vm->num_live_op);
	mvwprintw(menu, 17 + (4 * vm->num_of_champs), 24, "%d     ",\
	vm->cycles_to_die);
}
