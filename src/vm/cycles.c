/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 11:13:46 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cycle(t_vm *vm)
{
	t_cursor	*tmp;

	tmp = vm->cursors;
	while (tmp)
	{
		tmp->time_to_exec -= 1;
		if(!tmp->time_to_exec)
			ecec_op(tmp, )
		tmp = tmp->next;
	}
	vm->cycles += 1;
	while ()
}