/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 21:23:11 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	int i;
	t_options options;
	t_champ	*champs;
	t_vm	*vm;

	options = get_options(argc, argv);
	champs = read_champions_from_args(argc, argv);
	while (champs)
	{
		ft_printf("name     = %s\n", champs->name);
		ft_printf("comment  = %s\n", champs->comment);
		ft_printf("size     = %d\n", champs->code_size);
		ft_printf("magic    = %x\n", champs->magic);
		champs = champs->next;
	}
/*
	validity_core_args(argv + 1);
	vm = create_vm();
	argv++;
	while (*argv)
	{
		if (!ft_strcmp((const char*)*argv, "-n"))
			argv += 2;
		champ = get_champion_from_file(*argv);
		add_champion2end(&vm->champs, champ);
		argv++;
		ft_printf("champ name = %s\n", vm->champs->name);
	}
	vm->num_of_champs = count_champs(vm->champs);
	set_champ_code(vm);
	//dump_arena(vm->arena);
	destroy_vm(&vm);*/
	return (0);
}
