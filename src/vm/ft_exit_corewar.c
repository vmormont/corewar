/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_corewar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:58:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 10:32:15 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_exit(int err, char *file_name)
{
	if (err == FILE_FAILED)
		ft_fprintf(2, "Can't read source file %s\n", file_name);
	else if (err == INVALID_CHAMP_NUM)
		ft_fprintf(2, "Wrong champ number (1 - %d)\n", MAX_PLAYERS);
	else if (err == WAITING_FILE)
		ft_fprintf(2, "Error: corewar waiting for file with champ\n");
	else if (err == TYPE_ERROR)
		ft_fprintf(2, "Error: invalid type of file with champ\n");
	else if (err == USAGE)
		ft_fprintf(2, "%s\n%s\n", "./corewar  [-n {1 : MAX_PLAYERS}]",\
		"\t\t[-n] - set the certain serial number for next player");
	exit(err);
}
