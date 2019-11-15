/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:35:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/15 21:01:37 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		del_one_label(t_label **label)
{
	if (label && *label)
	{
		ft_strdel(&(*label)->name);
		(*label)->next = NULL;
		ft_memdel((void*)label);
	}
}

t_label		*new_label(size_t offset)
{
	t_label *label;

	if (!(label = (t_label*)malloc(sizeof(t_label))))
		return (NULL);
	ft_bzero((void*)label, sizeof(t_label));
	label->offset = offset;
	return (label);
}

void		del_label(t_label **begin)
{
	t_label	*temp;
	t_label	*label;

	if (begin && *begin)
	{
		label = *begin;
		while (label)
		{
			temp = label;
			label = label->next;
			del_one_label(&temp);
		}
		*begin = NULL;
	}
}

void		add_label2end(t_label **begin, t_label *label)
{
	t_label	*temp;

	if (begin)
	{
		if (!*begin)
			*begin = label;
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = label;
		}
	}
}

void		print_label(t_label *label)
{
	ft_printf("LABELS\n");
	ft_printf("_______________________________________\n");
	ft_printf("|       name       |      offset      |\n");
	while (label)
	{
		ft_printf("| %16s | %16d |\n", label->name, label->offset);
		label = label->next;
	}
	ft_printf("|_____________________________________|\n");
}
