/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/09 17:04:32 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main	(int argc, char **av)
{
	int			i;
	t_champ	*champ;

	champ = create_champ();
	ft_printf("%s = %d\n", "fork", get_op_code(champ->op_tab, "fork"));
	i = 0;
	if (argc == 1)
		ft_exit(USAGE);
	else
	{
		while (av[++i])
			create_cor_file(av[i]);
	}
	//free_champ(&champ);
	return (0);
}
