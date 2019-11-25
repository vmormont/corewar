/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_asm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/25 11:13:38 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_exit(t_champ **champ, int err)
{
	if (err == USAGE)
	{
		ft_fprintf(STDERR_FILENO, "%s\n%s%s\n",\
	"./asm\t[-a] <source_file.s>",\
	"\t[-a] - Instead of creating a .cor file, outputs a stripped and ",\
	"annotated version of the code to the standard output");
	}
	else if (err == FILE_EXTENSION_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: Invalid file extension. %s",\
		"Need <file_name>.s\n");
	else if (err == MALLOC_FAILURE)
		ft_fprintf(STDERR_FILENO, "Error: Failed to alloc memory\n");
	else if (err == NAME_LEN_ERROR)
		ft_fprintf(STDERR_FILENO, "Champion name too long (Max length %d)\n",\
		PROG_NAME_LENGTH);
	else if (err == COMMENT_LEN_ERROR)
		ft_fprintf(STDERR_FILENO, "%s (Max length %d)\n",\
		"Champion comment too long", COMMENT_LENGTH);
	else if (err == INVALID_OPTION)
		ft_fprintf(STDERR_FILENO, "Error: Invalid option\n");
	else
		perror("Error");
	free_champ(champ);
	exit(err);
}
