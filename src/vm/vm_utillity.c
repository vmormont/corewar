/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utillity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:59:44 by pcredibl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/11/26 13:23:47 by pcredibl         ###   ########.fr       */
=======
/*   Updated: 2019/11/26 13:18:11 by astripeb         ###   ########.fr       */
>>>>>>> d281da440f82b475415e3edee9d354788e0cab72
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

	i = 0;
	player = vm->champs;
	offset_start_code = MEM_SIZE / vm->num_of_champs;
	while(player)
	{
		ft_memcpy((void*)vm->arena + i, player->code, player->code_size);
		if (!(cursor	= new_cursor(i)))
			ft_exit(MALLOC_FAILURE, NULL, &vm);
		add_cursor(&vm->cursors, cursor);
		i += offset_start_code;
		player = player->next;
	}
}

/*int			read_memory(char *arena, int pos, char size)
{
	int 	offset;
	int		res;
	int		i;

	i = 0;
	res = 0;
	arena[2202] = 2;
	arena[2203] = 1;
	arena[2204] = 3;
	arena[2205] = 0;
	offset = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (i < size)
	{
		res = (arena[pos + offset + i] & 3) | (res << 1);
		i++;
	}
	return (res);
}*/

t_vm		*create_vm(t_champ *champs, t_options options)
{
	t_vm		*vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (NULL);
	ft_bzero((void*)vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->champs = champs;
	vm->num_of_champs = count_champs(vm->champs);
	vm->options = options;
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
