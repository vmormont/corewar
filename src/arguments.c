/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/14 19:45:36 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_args(t_arg **args, int num_args)
{
	int i;

	if (args && *args)
	{
		i = 0;
		while (i < num_args)
		{
			ft_memdel((void*)&(*args)[i].str);
			++i;
		}
		ft_memdel((void*)args);
	}
}

int		possible_arg(char arg, char mask)
{
	if (arg == T_REG && !(((mask >> 4) & T_REG) ^ T_REG))
		return (1);
	else if (arg == T_DIR && !(((mask >> 2) & T_DIR) ^ T_DIR))
		return (1);
	else if (arg == T_IND && !((mask & 3) ^ 3))
		return (1);
	return (0);
}

int		get_arguments(t_champ *champ, char *filedata, int index)
{
	int		j;
	char	n_com;

	//мы находимся на первом не 'пробельном' символе после инструкции
	j = i;
	
	i += filedata[i] == 'r' ? check_reg(champ,)

}