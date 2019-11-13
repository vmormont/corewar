/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:35:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/13 22:20:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		del_one_label(t_label **label)
{
	if (label && *label)
	{
		ft_strdel(&(*label)->name);
		(*label)->next = NULL;
		ft_memdel((void*)label);
	}
}

static t_label	*new_label(char *title, size_t offset)
{
	t_label *label;

	if (!(label = (t_label*)malloc(sizeof(t_label))))
		return (NULL);
	ft_bzero((void*)label, sizeof(t_label));
	label->name = title;
	label->offset = offset;
	return (label);
}

void			del_label(t_label **begin)
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

t_label			*add_label2end(t_label *begin, char *title, size_t offset)
{
	t_label	*temp;

	if (!begin)
	{
		if (!(begin = new_label(title, offset)))
			return (NULL);
		return (begin);
	}
	temp = begin;
	while (temp->next)
		temp = temp->next;
	if (!(temp->next = new_label(title, offset)))
	{
		del_label(&begin);
		return (NULL);
	}
	return (begin);
}

void			print_label(t_label *label)
{
	ft_printf("___________________ \n");
	ft_printf("|  name  | offset |\n");
	while (label)
	{
		ft_printf("| %6s | %6d |\n", label->name, label->offset);
		label = label->next;
	}
	ft_printf("|_________________|\n");
}
