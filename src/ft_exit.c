/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/12 21:31:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_exit(t_champ **champ, int err)
{
	if (err == USAGE)
		ft_fprintf(2, "Usage: ./asm <file name> (*.s)\n");
	else if (err == INVALID_FILE_NAME)
		ft_fprintf(2, "Error: Invalid input file\n");
	else if (err  == MALLOC_FAILURE)
		ft_fprintf(2, "Error: Failed to alloc memory\n");
	else
		perror("Error");
	free_champ(champ);
	exit(err);
}

void	lexical_error(t_champ **champ, char *data, char *err_adr)
{
	int		row;
	int		pos_in_row;
	int		pos;

	row = 1;
	pos_in_row = 1;
	pos = 0;
	while (&data[pos] != err_adr)
	{
		if (data[pos] == '\n')
		{
			row++;
			pos_in_row = 0;
		}
		pos++;
		pos_in_row++;
	}
	ft_fprintf(2, "Lexical error at [%03d]:[%03d]\n", row, pos_in_row);
	free_champ(champ);
	free(data);
	exit(LEXICAL_ERROR);
}
