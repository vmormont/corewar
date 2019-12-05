/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/06 00:21:32 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
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
		arena[index % MEM_SIZE] = (uint8_t)((num >> offset) & 0xFF);
		++i;
		++index;
		offset = offset - __CHAR_BIT__;
	}
}
*/

int			read_4_bytes(char *arena, unsigned int index)
{
	int i;
	int num;

	num = 0;
	index += (REG_SIZE - 1);
	i = REG_SIZE;
	while (i)
	{
		num += (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		--i;
		--index;
	}
	return (num);
}

short		read_2_bytes(char *arena, unsigned int index)
{
	int		i;
	short	num;

	num = 0;
	i = IND_SIZE;
	index += (IND_SIZE - 1);
	while (i)
	{
		num += (num << __CHAR_BIT__) | (uint8_t)arena[index % MEM_SIZE];
		--i;
		--index;
	}
	return (num);
}

void		copy_4_bytes(char *arena, unsigned int index, int num)
{
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		arena[index % MEM_SIZE] = num & 0xFF;
		++i;
		++index;
		num = num >> __CHAR_BIT__;
	}
}
