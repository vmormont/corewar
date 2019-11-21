/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_asm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 17:35:23 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_exit(t_champ **champ, int err)
{
	if (err == USAGE)
	{
		ft_fprintf(2, "%s\n%s%s\n",\
	"./asm\t[-a] <source_file.s>",\
	"\t[-a] - Instead of creating a .cor file, outputs a stripped and ",\
	"annotated version of the code to the standard output");
	}
	else if (err == INVALID_FILE_NAME)
		ft_fprintf(2, "Error: Invalid input file\n");
	else if (err == MALLOC_FAILURE)
		ft_fprintf(2, "Error: Failed to alloc memory\n");
	else if (err == NAME_LEN_ERROR)
		ft_fprintf(2, "Champion name too long (Max length %d)\n",\
		PROG_NAME_LENGTH);
	else if (err == COMMENT_LEN_ERROR)
		ft_fprintf(2, "Champion comment too long (Max length %d)\n",\
		COMMENT_LENGTH);
	else if (err == INVALID_OPTION)
		ft_fprintf(2, "Error: Invalid option\n");
	else
		perror("Error");
	free_champ(champ);
	exit(err);
}
