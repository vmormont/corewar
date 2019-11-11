/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/11 23:33:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_exit(t_champ **champ, int err)
{
	if (err == INVALID_FILE_NAME)
		ft_fprintf(2, "Error: Invalid input file\n");
	if (err  == MALLOC_FAILURE)
		ft_fprintf(2, "Error: Failed to alloc memory\n");
	if (err == USAGE)
		ft_fprintf(2, "Usage: ./asm <file name> (*.s)\n");
	free_champ(champ);
	exit(err);
}

void	lexical_error(t_champ **champ, int err, int ns, int i)
{
	if (err = NAME_ERROR)
		ft_fprintf(2, "Name error at [%03d]:[%03d]\n", ns, i);
	else
		ft_fprintf(2, "Lexical error at [%03d]:[%03d]\n", ns, i);
	free_champ(champ);
	exit(err);
}
