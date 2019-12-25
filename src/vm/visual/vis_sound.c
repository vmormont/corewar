/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sound.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 17:37:22 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/25 12:26:11 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vis_sound(t_visual *vis)
{
	vis->sound = vis->sound ? FALSE : TRUE;
	if (vis->sound)
		system("(afplay ./res/mk.mp3&)");
	else
		system("(pkill afplay)");
}
