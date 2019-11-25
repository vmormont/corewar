/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:35:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/25 14:38:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ			*create_new_champ(t_header *head, void *code)
{
	t_champ *champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero((void*)champ, sizeof(t_champ));
	if (!(champ->name = ft_strdup(head->prog_name))\
	|| !(champ->comment = ft_strdup(head->comment))\
	|| !(champ->code = ft_strnew(head->prog_size)))
	{
		del_one_champion(&champ);
		return (NULL);
	}
	ft_memcpy(champ->code, code, head->prog_size);
	champ->code_size = head->prog_size;
	champ->magic = head->magic;
	return (champ);
}

void			del_one_champion(t_champ **champ)
{
	if (champ && *champ)
	{
		(*champ)->next = NULL;
		ft_memdel((void*)&(*champ)->name);
		ft_memdel((void*)&(*champ)->comment);
		ft_memdel((void*)&(*champ)->code);
		ft_memdel((void*)champ);
	}
}

void			del_champions(t_champ **begin)
{
	t_champ	*first;
	t_champ	*second;

	if (begin && *begin)
	{
		first = *begin;
		while (first)
		{
			second = first;
			first = first->next;
			del_one_champion(&second);
		}
		*begin = NULL;
	}
}

void			add_champion2end(t_champ **begin, t_champ *champ)
{
	t_champ	*temp;

	if (begin)
	{
		if (!*begin)
		{
			*begin = champ;
			champ->id = 1;
		}
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = champ;
			champ->id = temp->id + 1;
		}
	}
}

void			insert_champion(t_champ **begin, t_champ *champ, int index)
{
	t_champ *temp;

	if (begin)
	{
		champ->id = index;
		if (!*begin || index == 1)
		{
			champ->next = *begin;
			*begin = champ;
		}
		else
		{
			temp = *begin;
			while (temp->next && champ->id > temp->next->id)
				temp = temp->next;
			if (temp->next)
				champ->next = temp->next;
			temp->next = champ;
		}
		set_champions_id(champ);
	}
}

void			print_champs(t_champ *champ)
{
	ft_printf("__________________________________\n");
	while (champ)
	{
		ft_printf("id      = %d\n", champ->id);
		ft_printf("magic   = %x\n", champ->magic);
		ft_printf("name    = %s\n", champ->name);
		ft_printf("comment = %s\n", champ->comment);
		ft_printf("size    = %d\n", champ->code_size);
		ft_printf("----------------------------------\n");
		champ = champ->next;
	}
}
