/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:06:22 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 17:58:48 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		kill_cursor(t_cursor **list, t_cursor *cursor)
{
	t_cursor	*start;
	t_cursor	*tmp;

	if (*list == cursor)
	{
		*list = cursor->next;
		cursor->next = NULL;
		free (cursor);
	}
	start = *list;
	while (cursor)
	{
		if (cursor->next && cursor->next == cursor)
		{
		tmp = cursor->next;
		cursor->next = cursor->next->next;
		tmp->next = NULL;
		free (tmp);
		break ;
		}
	cursor = cursor->next;
	}
	cursor = start;
}

void		kill_all_cursors(t_cursor **begin)
{
	t_cursor	*tmp;

	while (*begin)
	{
		tmp = *begin;
		(*begin) = (*begin)->next;
		tmp->next = NULL;
		free((void*)tmp);
	}
	begin = NULL;
}

void		add_cursor(t_cursor **list, t_cursor *cursor)
{
	cursor->next = *list;
	*list = cursor;
}

t_cursor	*copy_cursor(t_cursor *src, int pos, char mode)
{
	t_cursor	*dst;
	int			i;

	dst = (t_cursor*)malloc(sizeof(t_cursor));
	dst->carry = src->carry;
	dst->cycle_live = src->cycle_live;
	i = 0;
	while (++i <= REG_NUMBER)
		dst->reg[i] = src->reg[i];
	if (mode)
		dst->pos += pos;
	else
		dst->pos += (pos % IDX_MOD);
	dst->pos = dst->pos % IDX_MOD;
	return (dst);
}

t_cursor	*new_cursor(int pos)
{
	t_cursor	*cursor;
	static int	i = 1;

	cursor = (t_cursor*)malloc(sizeof(t_cursor));
	ft_bzero((void*)cursor, sizeof(t_cursor));
	cursor->id = ++i;
	cursor->pos = pos;
	return (cursor);
}
