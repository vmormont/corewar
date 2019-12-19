/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:53:13 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/20 00:12:11 by astripeb         ###   ########.fr       */
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
	if (PAIR_NUMBER(ch) == WHITE_TEXT || PAIR_NUMBER(ch) == FRAME)
		color_code = FRAME - 5;
	wcolor_set(vm->visual->arena, color_code + 5, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx",\
		vm->arena[i * DUMP_COLUMNS + j]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
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
	if (PAIR_NUMBER(ch) == FRAME || PAIR_NUMBER(ch) == WHITE_TEXT)
		color_code = WHITE_TEXT;
	wcolor_set(vm->visual->arena, color_code, NULL);
	if (vm->options.terminal != 2)
		mvwprintw(vm->visual->arena, i, j, "%02hhx",\
		vm->arena[i * DUMP_COLUMNS + j]);
	else
		mvwprintw(vm->visual->arena, i, j, "ff");
}

void		move_cursor(t_vm *vm, t_cursor *cursor)
{
	//в массиве положений кареток убираем одну каретку по старой позиции
	vm->visual->cursors_pos[cursor->pos] -= 1;
	if (vm->visual->cursors_pos[cursor->pos] == 0)
		clear_cursor(vm, cursor->pos, ft_abs(cursor->champ->id));

	if (vm->visual->cursors_pos[(cursor->pos + cursor->step) % MEM_SIZE] == 0)
		set_cursor(vm, (cursor->pos + cursor->step) % MEM_SIZE , ft_abs(cursor->champ->id));

	//в массив кареток добавляем одну каретку
	vm->visual->cursors_pos[(cursor->pos + cursor->step) % MEM_SIZE] += 1;

	wrefresh(vm->visual->arena);
}
