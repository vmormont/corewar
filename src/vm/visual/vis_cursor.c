/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:53:13 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/24 14:15:29 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_cursor(t_vm *vm, unsigned int pos)
{
	short	i;
	short	j;
	int		color;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	color = PAIR_NUMBER(mvwinch(vm->visual->arena, i, j));
	if (color < RED_CURSOR)
		color += 5;
	wcolor_set(vm->visual->arena, color, NULL);
	if (vm->options.terminal == NORMAL_MODE)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
	vm->visual->cursors_pos[pos] += 1;
}

void		clear_cursor(t_vm *vm, unsigned int pos)
{
	short	i;
	short	j;
	int		color;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	color = PAIR_NUMBER(mvwinch(vm->visual->arena, i, j));
	if (color > WHITE_TEXT && color < RED_LIVE)
		color -= 5;
	wcolor_set(vm->visual->arena, color, NULL);
	if (vm->options.terminal == NORMAL_MODE)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
}

void		move_cursor(t_vm *vm, t_cursor *cursor)
{
	if (vm->visual->cursors_pos[cursor->pos] > 0)
		vm->visual->cursors_pos[cursor->pos] -= 1;
	if (vm->visual->cursors_pos[cursor->pos] == 0)
		clear_cursor(vm, cursor->pos);
	if (vm->visual->cursors_pos[(cursor->pos + cursor->step) % MEM_SIZE] == 0)
		set_cursor(vm, (cursor->pos + cursor->step) % MEM_SIZE);
}

void		vis_st(t_vm *vm, int num, unsigned int pos, char color)
{
	short	i;
	short	j;
	short	k;
	int		c;
	char	offset;

	offset = 24;
	c = 0xFF;
	k = REG_SIZE;
	i = (pos % MEM_SIZE) / DUMP_ROWS;
	j = ((pos % MEM_SIZE) % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	wattron(vm->visual->arena, A_STANDOUT | A_BOLD);
	wcolor_set(vm->visual->arena, color, NULL);
	while (k--)
	{
		if (vm->options.terminal == 1)
			c = ((num >> offset) & 0xFF);
		mvwprintw(vm->visual->arena, i, j, "%02hhx", c);
		offset = offset - __CHAR_BIT__;
		j = (j + VIS_BYTE_SIZE) % ARENA_WIDTH;
		if (!j)
			++i;
		vm->visual->attr[(pos++) % MEM_SIZE].st_cycle = VIS_BACKLIGHT_NUM;
	}
	wattroff(vm->visual->arena, A_STANDOUT | A_BOLD);
}

void		vis_live(t_vm *vm, unsigned int pos, char color)
{
	short	i;
	short	j;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	if (!vm->visual->attr[pos].live_cycle)
	{
		vm->visual->attr[pos].instant_color =\
		PAIR_NUMBER(mvwinch(vm->visual->arena, i, j)) - 5;
	}
	wattron(vm->visual->arena, A_BOLD);
	wcolor_set(vm->visual->arena, color + 10, NULL);
	if (vm->options.terminal == NORMAL_MODE)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
	vm->visual->attr[pos].live_cycle = VIS_BACKLIGHT_NUM;
	wattroff(vm->visual->arena, A_BOLD);
}
