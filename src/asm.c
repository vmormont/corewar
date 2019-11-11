/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/11 23:41:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main	(int argc, char **argv)
{
	t_champ		*champ;
	char		*datafile;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	datafile = get_clean_data_from_file(champ, argv[1]);
	lexical_analizer(champ, datafile);
	free(datafile);
	free_champ(&champ);
	return (0);
}
