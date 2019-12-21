/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:53:13 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/21 12:20:16 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_cursor(t_vm *vm, unsigned int pos, int color_code)
{
	short i;
	short j;
	chtype ch;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * 3;

	//получаем символ по адресу
	ch = mvwinch(vm->visual->arena, i, j);
	//узнаем какой там цвет
	color_code = PAIR_NUMBER(ch);
	if (color_code < 6)
		color_code += 5;
	wcolor_set(vm->visual->arena, color_code, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");

	//в массив кареток добавляем одну каретку
	vm->visual->cursors_pos[pos] += 1;
}

void		clear_cursor(t_vm *vm, unsigned int pos, int color_code)
{
	short i;
	short j;
	chtype ch;

	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * 3;

	//получаем символ по адресу
	ch = mvwinch(vm->visual->arena, i, j);
	//узнаем какой там цвет
	color_code = PAIR_NUMBER(ch);
	if (color_code > 5)
		color_code -= 5;
	wcolor_set(vm->visual->arena, color_code, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx", vm->arena[pos]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
}

void		move_cursor(t_vm *vm, t_cursor *cursor)
{
	//в массиве положений кареток убираем одну каретку по старой позиции
	vm->visual->cursors_pos[cursor->pos] -= 1;
	if (vm->visual->cursors_pos[cursor->pos] == 0)
		clear_cursor(vm, cursor->pos, cursor->color);

	if (vm->visual->cursors_pos[(cursor->pos + cursor->step) % MEM_SIZE] == 0)
		set_cursor(vm, (cursor->pos + cursor->step) % MEM_SIZE , cursor->color);

	wrefresh(vm->visual->arena);
}

void		vis_st(t_vm *vm, int num, unsigned int pos, char color)
{
	short	i;
	short	j;
	short	k;
	char	offset;

	pos = pos % MEM_SIZE;
	i = pos / DUMP_ROWS;
	j = (pos % DUMP_COLUMNS) * 3;

	k = 0;
	offset = 24;
	wcolor_set(vm->visual->arena, color, NULL);
	while (k < REG_SIZE)
	{
		if (vm->options.terminal == 1)
			mvwprintw(vm->visual->arena, i, j, "%02hhx", ((num >> offset) & 0xFF));
		else
			mvwprintw(vm->visual->arena, i, j, "ff");
		offset = offset - __CHAR_BIT__;
		++k;
		j += 3;
		if (!(j % (DUMP_COLUMNS * 3)))
		{
			j = 0;
			++i;
		}
	}
//	wrefresh(vm->visual->arena);
}
