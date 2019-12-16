/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:55:43 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/16 22:36:07 by astripeb         ###   ########.fr       */
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
# define FRAME 6

/*
**	FUNCTION FOR VIZUALIZATION
*/

void			visualizator(t_vm *vm);

#endif
