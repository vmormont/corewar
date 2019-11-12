/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/12 21:23:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main	(int argc, char **argv)
{
	t_champ		*champ;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	lexical_analizer(champ, argv[1]);
	free_champ(&champ);
	return (0);
}
