/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/28 11:28:24 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_function g_operation[];

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
		cycle(vm);
	}
	else
		ft_exit_read(USAGE, NULL, &champs, NONE);
//	print_champs(vm->champs);

/*
// 	проверка на файле zork.cor
	ft_printf("pos = %d\n", vm->cursors->pos);
	g_operation[STI](vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + ARGS_SIZE + 1 + 2 + 2;
	ft_printf("and  = %d\n", vm->cursors->pos);
	g_operation[AND](vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + ARGS_SIZE + 1 + DIR_SIZE + 1;
	ft_printf("live = %d\n", vm->cursors->pos);
	g_operation[LIVE](vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + DIR_SIZE;
	ft_printf("zjmp = %d\n", vm->cursors->pos);
	g_operation[ZJMP](vm, vm->cursors);
	ft_printf("live = %d\n", vm->cursors->pos);
	dump_arena(vm->arena);
*/
	destroy_vm(&vm);
	return (0);
}

