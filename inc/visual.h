/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:55:43 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/17 20:19:25 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar_structs.h"

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
**	FUNCTION FOR VIZUALIZATION
*/

void			visualizator(t_vm *vm);

void			color_init(void);

void			show_values(t_vm *vm);

void			print_info(t_vm *vm);

void			print_src_arena(t_vm *vm, char *arena);

void			print_champ_info(t_vm *vm, t_champ *champs);

char			cursor_in_pos(int *cursors_map, int pos);

#endif
