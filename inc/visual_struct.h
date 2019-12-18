/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:20:45 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/18 15:56:14 by pcredibl         ###   ########.fr       */
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

typedef	struct				s_visual
{
	int						cursors_pos[MEM_SIZE];
	short					vis_speed;
	t_bool					pause;
}							t_visual;

#endif