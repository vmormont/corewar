/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:06:22 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 14:11:44 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		add_cursor(t_cursor **list, t_cursor *cursor)
{
	cursor->next = *list;
	*list = cursor;
}

t_cursor	*new_cursor(void)
{
	t_cursor	*cursor;

	cursor = (t_cursor*)malloc(sizeof(t_cursor));
	ft_bzero((void*)cursor, sizeof(t_cursor));
	return (cursor);
}