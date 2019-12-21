/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:55:43 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/20 21:04:42 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar_structs.h"
# include "visual_struct.h"

# define RED_TEXT 1
# define GREEN_TEXT 2
# define BLUE_TEXT 3
# define YELLOW_TEXT 4
# define WHITE_TEXT 5
# define RED_CURSOR 6
# define GREEN_CURSOR 7
# define BLUE_CURSOR 8
# define YELLOW_CURSOR 9
# define FRAME 10

/*
**	UTILITY
*/

t_visual 		*new_visual(void);

void			destroy_visual(t_visual **vis);

t_bool			cursor_in_pos(int *cursors_map, int pos);

void			clear_values(t_vm *vm);

/*
**	INITILIZE
*/

void			visualizator(t_vm *vm);

void			show_values(WINDOW *menu, t_vm *vm);

void			print_info(WINDOW *menu, t_vm *vm);

void			print_arena(t_vm *vm, char *arena);

void			print_champ_info(WINDOW *menu, t_vm *vm, t_champ *champs);

void			vis_cycle(t_vm *vm);

/*
**	VISUALISATION CURSOR
*/

void			set_cursor(t_vm *vm, unsigned int pos, int color_code);

void			clear_cursor(t_vm *vm, unsigned int pos, int color_code);

void			move_cursor(t_vm *vm, t_cursor *cursor);

void			vis_st(t_visual *vis, int num, int pos, char color);

#endif
