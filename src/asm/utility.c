/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:46:25 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/20 16:24:07 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern		t_op g_op_tab[];

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
	int		i;

	i = 0;
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

char		*ft_strlstr(char *src, char *pattern, int len)
{
	int			i;

	len -= (ft_strlen(pattern) - 1);
	while (len >= 0)
	{
		if (src[len] == pattern[0])
		{
			i = 1;
			while ((src[len + i] == pattern[i]) && pattern[i])
				++i;
			if (!pattern[i])
				return (src + len);
		}
		len--;
	}
	return (NULL);
}

int			isseparator(char c)
{
	if (c == DIRECT_CHAR || c == '-' || ft_isspace(c))
		return (1);
	return (0);
}

int			isinstruct(char *name)
{
	int i;
	int	code;

	i = 1;
	code = 0;
	while (i <= NUMBER_OF_INSTR)
	{
		if (!ft_strncmp(g_op_tab[i].name, name, ft_strlen(g_op_tab[i].name)))
			code = i;
		++i;
	}
	return (code);
}
