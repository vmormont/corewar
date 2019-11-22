/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utillity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:59:44 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 18:40:34 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_champ_code(t_vm *vm)
{
	t_champ		*player;
	int			offset_start_code;
	int			i;
	t_cursor	*cursor;

	offset_start_code = MEM_SIZE / vm->num_of_champs;
	player = vm->champs;
	i = 0;
	while(player)
	{
		ft_memcpy((void*)vm->arena + i, (void*)player->code, player->code_size);
		cursor	= new_cursor(i);
		add_cursor(&vm->cursors, cursor);
		i += offset_start_code;
		player = player->next;
	}
}

t_vm	*create_vm(void)
{
	t_vm		*vm;

	vm = (t_vm*)malloc(sizeof(t_vm));
	ft_bzero((void*)vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	//vm->champs = champs;
	//vm->num_of_champs = count_champs(vm->champs);
	return (vm);
}

void	destroy_vm(t_vm **vm)
{
	if (vm && (*vm))
	{
		del_champions(&(*vm)->champs);
		kill_all_cursors(&(*vm)->cursors);
		vm && (*vm) ? free((void*)(*vm)) : 0;
		vm = NULL;
	}
}
