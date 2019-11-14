/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/14 21:46:55 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_champ		*champ;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	lexical_analizer(champ, argv[1]);
	free_champ(&champ);
	return (0);
}

void		lexical_analizer(t_champ *champ, char *filename)
{
	int		i;
	char	*filedata;

	filedata = get_clean_data_from_file(champ, filename);
	i = parse_name(champ, filedata);
	i = parse_instruction(champ, filedata, i);
}
