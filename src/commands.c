/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:24:27 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/13 18:27:21 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void detect_label(t_champ *champ, char **data)
{
	int		i;

	i = 0;
	while (!ft_isspace((*data)[i]) && (*data)[i] != ':')
		i++;
	if ((*data)[i] == ':')
	{
		champ->labels = add_label2end(champ->labels, ft_strsub((const char*)*data, 0, i));
		*data += i + 1;
	}	
	//ft_printf("label name = %s\n", champ->labels->name);
	//ft_printf("data = %s\n", *data);
}

void	parse_instr(t_champ *champ, char *filedata)
{
	int		offset;

	detect_label(champ, &filedata);
}