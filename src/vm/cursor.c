/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:06:22 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/10 23:19:36 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cursor	*new_cursor(unsigned int pos)
{
	t_cursor	*cursor;
	static int	i = 1;

	if (!(cursor = (t_cursor*)malloc(sizeof(t_cursor))))
		return (NULL);
	ft_bzero((void*)cursor, sizeof(t_cursor));
	cursor->id = i;
	cursor->pos = pos;
	cursor->exec = TRUE;
	++i;
	return (cursor);
}

void		kill_cursor(t_cursor **list, t_cursor *cursor)
{
	t_cursor	*first;
	t_cursor	*temp;

	if (*list == cursor)
	{
		*list = cursor->next;
		ft_memdel((void*)&cursor);
	}
	else
	{
		first = *list;
		while (first)
		{
			if (first->next == cursor)
			{
				temp = first->next;
				first->next = temp->next;
				temp->next = NULL;
				ft_memdel((void*)&temp);
				break ;
			}
			first = first->next;
		}
	}
}

void		kill_all_cursors(t_cursor **begin)
{
	t_cursor	*tmp;

	while (*begin)
	{
		tmp = *begin;
		(*begin) = (*begin)->next;
		ft_memdel((void*)&tmp);
	}
	begin = NULL;
}

void		add_cursor(t_cursor **list, t_cursor *cursor)
{
	cursor->next = *list;
	*list = cursor;
}

t_cursor	*copy_cursor(t_cursor *src, unsigned int pos)
{
	t_cursor	*dst;
	int			i;

	if (!(dst = new_cursor(pos)))
		return (NULL);
	dst->carry = src->carry;
	dst->cycle_live = src->cycle_live;
	i = -1;
	while (++i <= REG_NUMBER)
		dst->reg[i] = src->reg[i];
	return (dst);
}
