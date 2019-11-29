/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/29 17:56:01 by pcredibl         ###   ########.fr       */
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
	if (!champs)
		ft_exit_read(USAGE, NULL, &champs, NONE);
	vm = create_vm(champs, options);
	set_champ_code_on_arena(vm);
	introduce(vm->champs);
	cycle(vm);
//	print_champs(vm->champs);
//	dump_arena(vm->arena);
//	ft_printf("cycles = %d\n", vm->cycles);

/*
	int n = -40;
	unsigned int u_n = (unsigned int)n;
	ft_printf("n = %d, u_n = %u, u_n %% MEM_SIZE = %u\n",
	n, u_n, u_n % MEM_SIZE);
*/
	destroy_vm(&vm);
	return (0);
}

