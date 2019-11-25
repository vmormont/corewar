/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:39:58 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/25 19:55:17 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_champions_id(t_champ *champ)
{
	t_champ *temp;

	if (champ->next)
	{
		temp = champ->next;
		temp->id = champ->id + 1;
		while (temp->next)
		{
			temp->next->id = temp->id + 1;
			temp = temp->next;
		}
	}
}

int			count_champs(t_champ *champs)
{
	int	i;

	i = 0;
	while (champs)
	{
		i++;
		champs = champs->next;
	}
	return (i);
}

t_champ		*get_champ_by_id(t_champ *champs, int id)
{
	while (champs)
	{
		if (champs->id == id)
			return (champs);
		champs = champs->next;
	}
	return (champs);
}
