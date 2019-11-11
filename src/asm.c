/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/11 16:08:02 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main	(int argc, char **argv)
{
	int			i;
	t_champ		*champ;
	int			fd;
	char		*datafile;
	//char		*str;
	//char		**str2;

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
	champ = lexical_analizer(champ, datafile);
	free(datafile);
	/*str = "\n";
	str2 = ft_strsplit(str, '\n');
	ft_printf("str = %s\n", str2[0]);
	str2 = ft_strsplit(*str2, '\n');
	ft_printf("str = %s\n", str2[0]);*/
	free_champ(&champ);
	close(fd);
	return (0);
}
