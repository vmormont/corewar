/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_egg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:13:32 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/25 12:20:58 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	easter_egg(t_vm *vm)
{
	wattron(vm->visual->menu, A_BOLD);
	wcolor_set(vm->visual->menu, RED_TEXT, NULL);
	mvwprintw(vm->visual->menu, 35 + (4 * vm->num_of_champs), 10,\
	"Your soul is mine!!");
	wcolor_set(vm->visual->menu, WHITE_TEXT, NULL);
}
