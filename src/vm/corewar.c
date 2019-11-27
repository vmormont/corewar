/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/27 11:59:20 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	int			i;
	t_options	options;
	t_champ		*champs;
	t_vm		*vm;

	champs = NULL;
	options = get_options(argc, argv);
	read_champions_from_args(argc, argv, &champs);
	if (champs)
	{
		vm = create_vm(champs, options);
		set_champ_code_on_arena(vm);
		op_ld(vm, vm->cursors);
		cycle(vm);
	}
	else
		ft_exit_read(USAGE, NULL, &champs, NONE);
//	print_champs(vm->champs);
/*
	vm->arena[3] = 0xFF;
	int num = read_4_bytes(vm->arena, 0);
	copy_4_bytes(vm->arena, 2048, num);
	short sh = read_2_bytes(vm->arena, 14);
	copy_2_bytes(vm->arena, 4095, sh);
	dump_arena(vm->arena);
*/
	destroy_vm(&vm);
	return (0);
}

