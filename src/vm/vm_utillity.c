/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utillity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:59:44 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/06 20:14:31 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op g_op_tab[];

static int	count_champs(t_champ *champs)
{
	int	i;

	i = 0;
	while (champs)
	{
		i++;
		champs = champs->next;
	}
	return (i);
}

void		set_champ_code_on_arena(t_vm *vm)
{
	int			i;
	t_champ		*player;
	t_cursor	*cursor;
	int			offset_start_code;
	char		op_code;

	i = 0;
	player = vm->champs;
	offset_start_code = MEM_SIZE / vm->num_of_champs;
	while(player)
	{
		ft_memcpy((void*)vm->arena + i, player->code, player->code_size);
		if (!(cursor	= new_cursor(i)))
			ft_exit(MALLOC_FAILURE, NULL, &vm);
		cursor->reg[1] = player->id;
		op_code = vm->arena[i];
		cursor->op_code = op_code;
		cursor->cycles2go = g_op_tab[op_code].cycles2go;
		cursor->pos = i;
		add_cursor(&vm->cursors, cursor);
		i += offset_start_code;
		player = player->next;
	}
}

t_vm		*create_vm(t_champ *champs, t_options options)
{
	t_vm		*vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (NULL);
	ft_bzero((void*)vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles = 0;
	vm->checks_without_dec_cycle2die = 1;
	vm->champs = champs;
	vm->num_of_champs = count_champs(vm->champs);
	vm->options = options;
	vm->checks_without_dec_cycle2die = 1;
	return (vm);
}

void	destroy_vm(t_vm **vm)
{
	if (vm && (*vm))
	{
		del_champions(&(*vm)->champs);
		kill_all_cursors(&(*vm)->cursors);
		ft_memdel((void*)vm);
	}
}
