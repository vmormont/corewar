/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:52:36 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/09 13:05:40 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_champ		*create_champ(void)
{
	t_champ	*champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	champ->name = NULL;
	champ->comment = NULL;
	champ->instr = NULL;
	champ->labels = NULL;
	champ->op_tab = create_op_tab();
	if (!champ->op_tab)
	{
		free(champ);
		return (NULL);
	}
	return (champ);
}

void		free_champ(t_champ **champ)
{
	if (champ && *champ)
	{
		ft_strdel(&(*champ)->name);
		ft_strdel(&(*champ)->comment);
		ft_memdel((void*)&(*champ)->op_tab);
		/* не забыть вставить финкции очистки */
		(*champ)->instr = NULL;
		(*champ)->labels = NULL;
		free(*champ);
		*champ = NULL;
	}
}
