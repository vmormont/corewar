/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 12:51:13 by astripeb         ###   ########.fr       */
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
	else if (err  == NAME_LEN_ERROR)
		ft_fprintf(2, "Champion name too long (Max length %d)\n",\
		PROG_NAME_LENGTH);
	else if (err  == COMMENT_LEN_ERROR)
		ft_fprintf(2, "Champion comment too long (Max length %d)\n",\
		COMMENT_LENGTH);
	else if (err  == EXEC_CODE_ERROR)
		ft_fprintf(2, "Error: Exec code of champion too big. Max size %d.\n",\
		 CHAMP_MAX_SIZE);
	else
		perror("Error");
	free_champ(champ);
	exit(err);
}
