/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:53:13 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/21 17:36:02 by astripeb         ###   ########.fr       */
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
	//получаем символ по адресу и узнаем какой там цвет
	color = PAIR_NUMBER(mvwinch(vm->visual->arena, i, j));
	if (color < 6)
		color += 5;
	wcolor_set(vm->visual->arena, color, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");

	//в массив кареток добавляем одну каретку
	vm->visual->cursors_pos[pos] += 1;
}

void		clear_cursor(t_vm *vm, unsigned int pos)
{
	short	i;
	short	j;
	int		color;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * VIS_BYTE_SIZE;

	//получаем символ по адресу и узнаем какой там цвет
	color = PAIR_NUMBER(mvwinch(vm->visual->arena, i, j));
	if (color > 5 && color <= FRAME)
		color -= 5;
	wcolor_set(vm->visual->arena, color, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
}

void		move_cursor(t_vm *vm, t_cursor *cursor)
{
	//в массиве положений кареток убираем одну каретку по старой позиции
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
	char	offs;

	k = 0;
	offs = 24;
	i = (pos % MEM_SIZE) / DUMP_ROWS;
	j = ((pos % MEM_SIZE) % DUMP_COLUMNS) * VIS_BYTE_SIZE;
	wcolor_set(vm->visual->arena, color, NULL);
	while (k < REG_SIZE)
	{
		if (vm->options.terminal == 1)
			mvwprintw(vm->visual->arena, i, j, "%02hhx", (num >> offs) & 0xFF);
		else
			mvwprintw(vm->visual->arena, i, j, "ff");
		offs = offs - __CHAR_BIT__;
		++k;
		j += VIS_BYTE_SIZE;
		if (!(j % ARENA_WIDTH))
		{
			j = 0;
			++i;
		}
	}
}
