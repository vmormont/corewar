/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:35:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/21 15:43:09 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_champ		*create_new_champ(char *name, char *comment, int code_size)
{
	t_champ *champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	if (!(champ->name = ft_strdup(name)))
	{
		ft_memdel((void*)&champ);
		return (NULL);
	}
	if (!(champ->comment = ft_strdup(comment)))
	{
		ft_memdel((void*)&champ->name);
		ft_memdel((void*)&champ);
		return (NULL);
	}
	champ->code_size = code_size;
	champ->next = NULL;
	return (champ);
}

void		add_champ2end(t_champ **begin, t_champ *champ)
{
	t_champ	*temp;

	if (begin)
	{
		if (!*begin)
			*begin = champ;
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = champ;
		}
	}
}
