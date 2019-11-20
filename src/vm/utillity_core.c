/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utillity_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:58:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 20:59:49 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_exit_core(int err, char *file_name)
{
	if (err == FILE_FAILED)
		ft_printf("Can't read source file %s\n", file_name);
	else if (err == INVALID_CHAMP_NUM)
		ft_printf("Wrong champ number (1 - %d)\n", MAX_PLAYERS);
	else if (err == WAITING_FILE)
		ft_printf("Error: corewar waiting for file with champ\n");
	else if (err == TYPE_ERROR)
		ft_printf("Error: invalid type of file with champ\n");
	exit(err);
}
