/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:55:43 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/24 17:38:54 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar_structs.h"
# include "visual_struct.h"

enum	e_vis_color
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
	FRAME,
	RED_LIVE,
	GREEN_LIVE,
	BLUE_LIVE,
	YELLOW_LIVE
};

# define VIS_MIN_SPEED 1
# define VIS_MAX_SPEED 1000
# define VIS_SPEED_START 100
# define VIS_SPEED_DEL 1000000

# define VIS_BYTE_SIZE 3
# define ARENA_WIDTH (VIS_BYTE_SIZE * DUMP_COLUMNS)
# define ARENA_HEIGHT (DUMP_ROWS)

# define VIS_BACKLIGHT_NUM 50

/*
**	UTILITY
*/

t_visual		*new_visual(void);

void			destroy_visual(t_visual **vis);

void			show_values(WINDOW *menu, t_vm *vm);

/*
**	INITILIZE
*/

void			visualizator(t_vm *vm);

void			print_arena(t_vm *vm);

void			vis_cycle(t_vm *vm);

/*
**	VISUALISATION CURSOR
*/

void			set_cursor(t_vm *vm, unsigned int pos);

void			clear_cursor(t_vm *vm, unsigned int pos);

void			move_cursor(t_vm *vm, t_cursor *cursor);

void			vis_st(t_vm *vm, int num, unsigned int pos, char color);

void			vis_live(t_vm *vm, unsigned int pos, char color);

void			check_attr(t_vm *vm);

/*
**	SOUND
*/

void			vis_sound(t_visual *vis);

#endif
