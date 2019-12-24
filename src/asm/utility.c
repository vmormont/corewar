/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:46:25 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/24 21:47:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_error_position(char *data, char *error_address)
{
	int		i;
	int		row;
	int		pos_in_row;

	i = 0;
	row = 1;
	pos_in_row = 1;
	while (&data[i] != error_address)
	{
		if (data[i] == '\n')
		{
			row++;
			pos_in_row = 0;
		}
		i++;
		pos_in_row++;
	}
	ft_fprintf(2, "[%03d:%03d]", row, pos_in_row);
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

t_bool		isseparator(char c)
{
	if (c == DIRECT_CHAR || c == '-' || ft_isspace(c))
		return (TRUE);
	return (FALSE);
}
