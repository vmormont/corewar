/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
<<<<<<< HEAD:src/vm/live_st_sti_aff.c
/*   Updated: 2019/11/26 14:21:49 by pcredibl         ###   ########.fr       */
=======
/*   Updated: 2019/11/26 14:22:38 by astripeb         ###   ########.fr       */
>>>>>>> d281da440f82b475415e3edee9d354788e0cab72:src/vm/copy_read.c
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			read_4_bytes(char *arena, int index)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (i < DIR_SIZE)
	{
<<<<<<< HEAD:src/vm/live_st_sti_aff.c
		num |= arena[index % MEM_SIZE];
		i != DIR_SIZE - 1 ? num = num << 8 : 0;
=======
		num = (num << __CHAR_BIT__) | (unsigned char)arena[index % MEM_SIZE];
>>>>>>> d281da440f82b475415e3edee9d354788e0cab72:src/vm/copy_read.c
		++i;
		++index;
	}
	return (num);
}

short		read_2_bytes(char *arena, int index)
{
	int		i;
	short	num;

	num = 0;
	i = 0;
	while (i < IND_SIZE)
	{
<<<<<<< HEAD:src/vm/live_st_sti_aff.c
		num |= arena[index % MEM_SIZE];
		num = num << 8;
=======

		num = (num << __CHAR_BIT__) | (unsigned char)arena[index % MEM_SIZE];
>>>>>>> d281da440f82b475415e3edee9d354788e0cab72:src/vm/copy_read.c
		++i;
		++index;
	}
	return (num);
}


void		copy_4_bytes(char *arena, int index, int num)
{
	int 	i;
	int		offset;

	i = 0;
	offset = __CHAR_BIT__;
	while (i < REG_SIZE)
	{
		arena[index % MEM_SIZE] = (num >> offset) & 0xFF;
		++index;
		++i;
		offset = offset - __CHAR_BIT__;
	}
}

void		copy_2_bytes(char *arena, int index, short num)
{
	int 	i;
	int		offset;

	i = 0;
	offset = __CHAR_BIT__;
	while (i < IND_SIZE)
	{
		arena[index % MEM_SIZE] = (num >> offset) & 0xFF;
		++index;
		++i;
		offset = offset - __CHAR_BIT__;
	}
}
