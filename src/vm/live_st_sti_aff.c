/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_st_sti_aff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/26 14:21:49 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			read_4_bytes(char *arena, int index)
{
	int i;
	int num;

	num = 0;
	i = 0;
	while (i < DIR_SIZE)
	{
		num |= arena[index % MEM_SIZE];
		i != DIR_SIZE - 1 ? num = num << 8 : 0;
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
	while (i < REG_SIZE)
	{
		num |= arena[index % MEM_SIZE];
		num = num << 8;
		++i;
		++index;
	}
	return (num);
}

/*
void		copy_4_bytes(char *arena, int index, int num)
{
	int 	i;
}
void		live(t_vm *vm, t_cursor *cursor)
{

}
*/
