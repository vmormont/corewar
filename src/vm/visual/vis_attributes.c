/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 09:42:39 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 22:50:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	clear_attributes(t_visual *vis, char *arena,\
			unsigned int pos, char mode)
{
	int		i;
	int		j;
	char	color;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	color = PAIR_NUMBER(mvwinch(vis->arena, i, j));
	if (PAIR_NUMBER(mvwinch(vis->arena, i, j)) > FRAME)
		color = vis->attr[pos].instant_color;
	wcolor_set(vis->arena, color, NULL);
	if (mode == NORMAL_MODE)
		mvwprintw(vis->arena, i, j, "%02hhx", arena[pos]);
	else
		mvwprintw(vis->arena, i, j, "ff");
}

void		check_attr(t_vm *vm)
{
	unsigned int	i;
	char			mode;
	t_attr			*attr;

	i = 0;
	mode = vm->options.terminal;
	attr = vm->visual->attr;
	while (i < MEM_SIZE)
	{
		if (attr[i].st_cycle > 0)
		{
			attr[i].st_cycle -= 1;
			if (!attr[i].st_cycle)
				clear_attributes(vm->visual, vm->arena, i, mode);
		}
		if (attr[i].live_cycle > 0)
		{
			attr[i].live_cycle -= 1;
			if (!attr[i].live_cycle)
				clear_attributes(vm->visual, vm->arena, i, mode);
		}
		++i;
	}
}
