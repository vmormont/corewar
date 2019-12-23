/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stpaste.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:53:57 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 15:23:11 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		add_stpaste(short row, short col, char color, t_vm *vm)
{
	t_stpaste		*instance;
	t_stpaste		*temp;

	if (!(instance = new_stpaste(row, col, color, vm->cycles)))
		ft_exit(MALLOC_FAILURE, &vm);
	temp = vm->visual->paste;
	if (!temp)
		vm->visual->paste = instance;
	else
	{
		while (temp->next)
		{
			
		}
	}
	
}