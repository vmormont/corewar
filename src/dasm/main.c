/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:57:32 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/21 17:22:08 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int				main(int argc, char **argv)
{
	bool		error;
	int			index;

	error = false;
	index = 1;
	while (index < argc)
	{
		if (is_filename_extension(argv[index], ".cor"))
			disassemble(argv, index);
		else
		{
			error = true;
			ft_printf("{red}ERROR: invalid filename extension: %s{eoc}\n",\
						argv[index]);
		}
		++index;
	}
	if (error || argc == 1)
		print_usage();
	return (EXIT_SUCCESS);
}
