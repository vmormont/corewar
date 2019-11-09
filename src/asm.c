/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/09 17:49:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main	(int argc, char **argv)
{
	int			i;
	t_champ		*champ;
	int			fd;
	char		*datafile;

	champ = create_champ();
	i = 0;
/*
	if (argc == 1)
		ft_exit(USAGE);
	else
	{
		while (argv[++i])
			create_cor_file(argv[i]);
	}
*/
	fd = open(argv[1], O_RDONLY);
	datafile = read_from_file_to_var(fd);
	ft_printf("BEFORE\n{red}%s{eoc}", datafile);
	clean_commetns(datafile);
	ft_printf("\n\nAFTER\n%s", datafile);
	free(datafile);
	free_champ(&champ);
	close(fd);
	return (0);
}
