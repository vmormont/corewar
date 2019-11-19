/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:46:25 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/19 19:24:18 by astripeb         ###   ########.fr       */
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

int			skip_spaces(char *filedata, int index)
{
	while (ft_isspace(filedata[index]) && filedata[index] != '\n')
		++index;
	return (index);
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
