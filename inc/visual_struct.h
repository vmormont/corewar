/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:20:45 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/19 00:09:09 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_STRUCT_H
# define VISUAL_STRUCT_H
# include "op.h"
# include "op_struct.h"
# include "libftprintf.h"

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
	short			vis_speed;
	t_bool			pause;
}					t_visual;

#endif
