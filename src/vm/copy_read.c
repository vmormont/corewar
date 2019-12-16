/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/13 19:36:14 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			read_4_bytes(char *arena, unsigned int index)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (i < DIR_SIZE)
	{
		num = (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		++i;
		++index;
	}
	return (num);
}

short		read_2_bytes(char *arena, unsigned int index)
{
	int		i;
	short	num;

	num = 0;
	i = 0;
	while (i < IND_SIZE)
	{
		num = (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		++i;
		++index;
	}
	return (num);
}

void		copy_4_bytes(char *arena, unsigned int index, int num)
{
	int		i;
	char	offset;

	i = 0;
	offset = 24;
	while (i < REG_SIZE)
	{
		arena[index % MEM_SIZE] = (unsigned char)((num >> offset) & 0xFF);
		++i;
		++index;
		offset = offset - __CHAR_BIT__;
	}
}

int			read_to_int(char *arena, unsigned int index, char size)
{
	if (size == IND_SIZE)
		return (read_2_bytes(arena, index));
	return (read_4_bytes(arena, index));
}
