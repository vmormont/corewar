/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/05 17:30:38 by pcredibl         ###   ########.fr       */
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
		num = (num << __CHAR_BIT__) | (unsigned char)arena[index % MEM_SIZE];
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
		num = (num << __CHAR_BIT__) | (unsigned char)arena[index % MEM_SIZE];
		++i;
		++index;
	}
	return (num);
}

void		copy_4_bytes(char *arena, unsigned index, int num)
{
	int		i;
	int		offset;

	i = 0;
	offset = 24;
	while (i < REG_SIZE)
	{
		arena[index % MEM_SIZE] = (num >> offset) & 0xff;
		++index;
		++i;
		offset = offset - __CHAR_BIT__;
	}
}
