/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 20:28:49 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	int			i;
	char		dump;
	t_champ		*champ;

	i = 1;
	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	dump = options(argc - 1, &argv[1]);
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			champ = create_champ();
			asm_file_parser(champ, argv[i]);
			if (dump)
				dump_to_stdout(champ);
			else
				assembly(champ, argv[i]);
			free_champ(&champ);
		}
		++i;
	}
	return (0);
}
