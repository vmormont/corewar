/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/25 13:53:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	int			i;
	t_options	options;
	t_champ		*champs;
	t_vm		*vm;

	options = get_options(argc, argv);
	champs = read_champions_from_args(argc, argv);
	if (champs)
	{
		vm = create_vm(champs, options);
		set_champ_code_on_arena(vm);
//		cycle(vm);
	}
	else
		ft_exit_read(USAGE, NULL, &champs, NONE);
	print_champs(vm->champs);
//	dump_arena(vm->arena);
	destroy_vm(&vm);
	return (0);
}

