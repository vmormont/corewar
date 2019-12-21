/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:55:43 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/21 13:00:12 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar_structs.h"
# include "visual_struct.h"

enum	s_vis_color
{
	RED_TEXT = 1,
	GREEN_TEXT,
	BLUE_TEXT,
	YELLOW_TEXT,
	WHITE_TEXT,
	RED_CURSOR,
	GREEN_CURSOR,
	BLUE_CURSOR,
	YELLOW_CURSOR,
	FRAME
};

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

void			show_values(WINDOW *menu, t_vm *vm);

/*
**	INITILIZE
*/

void			visualizator(t_vm *vm);

void			print_arena(t_vm *vm, char *arena);

void			vis_cycle(t_vm *vm);

/*
**	VISUALISATION CURSOR
*/

void			set_cursor(t_vm *vm, unsigned int pos, int color_code);

void			clear_cursor(t_vm *vm, unsigned int pos, int color_code);

void			move_cursor(t_vm *vm, t_cursor *cursor);

void			vis_st(t_vm *vm, int num, unsigned int pos, char color);

#endif
