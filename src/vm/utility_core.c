/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:47:36 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 22:58:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		dump_arena(char *arena)
{
	int i;
	int j;
	char *address;

	i = 0;
	address = NULL;
	while (i < DUMP_COLUMNS)
	{
		j = 0;
		ft_printf("%06p : ", (void*)address);
		while (j < DUMP_ROWS)
		{
			ft_printf("%x%x ", (arena[DUMP_ROWS * i + j] & 0xF0) >> 4,\
			arena[DUMP_ROWS * i + j] & 0xF);
			++j;
			++address;
		}
		ft_printf("\n");
		++i;
	}
}

int			reverse_bits(int num, char full_bit)
{
	int		rev_num;

	if (full_bit)
	{
		rev_num = (num & 0xFF) << 24;
		rev_num = rev_num | ((num >> 8) & 0xFF) << 16;
		rev_num = rev_num | ((num >> 16) & 0xFF) << 8;
		rev_num = rev_num | ((num >> 24) & 0xFF);
	}
	else
	{
		rev_num = (num & 0xFF) << 8;
		rev_num = rev_num | ((num & 0xFF00) >> 8);
	}
	return (rev_num);
}

t_bool		isdigit_word(char *word)
{
	if (!word)
		return (FALSE);
	while (ft_isdigit(*word))
		++word;
	if (*word)
		return (FALSE);
	return (TRUE);
}

t_bool		is_filename_extension(char *filename, char *extension)
{
	filename = ft_strrchr(filename, '.');
	if (filename)
	{
		if (!ft_strcmp(filename, extension))
			return (TRUE);
	}
	return (FALSE);
}

void		ft_swap(void **a, void **b)
{
	void	*c;

	c = *a;
	*a = *b;
	*b = c;
}
