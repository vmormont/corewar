/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:39:58 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/26 15:25:03 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

static void	check_champs_num(t_champ *champs)
{
	int			i;
	t_champ		*temp;

	i = 1;
	temp = champs;
	while (temp)
	{
		temp->id = ft_abs(temp->id);
		if (temp->id > MAX_PLAYERS)
			ft_exit_read(MANY_CHAMPS_ERROR, NULL, &champs, NONE);
		if (temp->id != i)
			ft_exit_read(USAGE, NULL, &champs, NONE);
		++i;
		temp->id = -temp->id;
		temp = temp->next;
	}
}

static void	swap_champs(t_champ *one, t_champ *two)
{
	ft_swap((void**)&one->id, (void**)&two->id);
	ft_swap((void**)&one->comment, (void**)&two->comment);
	ft_swap((void**)&one->name, (void**)&two->name);
	ft_swap((void**)&one->code, (void**)&two->code);
	ft_swap((void**)&one->code_size, (void**)&two->code_size);
}

static void	set_id_none_champs(t_champ *champs)
{
	t_champ	*first;
	t_champ	*temp;
	int		i;

	first = champs;
	while (first)
	{
		if (!first->id)
		{
			i = 1;
			while (i <= MAX_PLAYERS)
			{
				if (!(temp = get_champ_by_id(champs, i)))
				{
					first->id = i;
					break ;
				}
				++i;
			}
		}
		first = first->next;
	}
}

void		sort_and_check_champs(t_champ *begin)
{
	t_champ *first;
	t_champ *second;

	set_id_none_champs(begin);
	first = begin;
	while (first)
	{
		second = first->next;
		while (second)
		{
			if (first->id > second->id)
				swap_champs(first, second);
			second = second->next;
		}
		first = first->next;
	}
	check_champs_num(begin);
}
