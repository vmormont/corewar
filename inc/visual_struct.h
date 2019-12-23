/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:20:45 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 17:03:56 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_STRUCT_H
# define VISUAL_STRUCT_H
# include "op.h"
# include "op_struct.h"
# include "libftprintf.h"

typedef struct		s_attr
{
	char	live_cycle;
	char	st_cycle;
	char	instant_color;
}					t_attr;

/*
** cursor_pos[MEM_SIZE]		- карта наличия курсоров на арене
** vis_speed				- скорость отрисовки (циклов в секунду)
** pause					- флаг, стоит ли игра на паузе.
*/

typedef	struct		s_visual
{
	WINDOW			*arena;
	WINDOW			*menu;
	int				cursors_pos[MEM_SIZE];
	struct s_attr	attr[MEM_SIZE];
	short			vis_speed;
	t_bool			pause;
}					t_visual;

#endif
