/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_st_sti_aff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:44:46 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/25 21:03:36 by astripeb         ###   ########.fr       */
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
		num = num << 2;
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
		num = num << 2;
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
