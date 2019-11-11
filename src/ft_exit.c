/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/11 15:53:54 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit(int err)
{
	if (err == INVALID_FILE_NAME)
		exit(ft_fprintf(2, "Invalid input file\n"));
	if (err == USAGE)
		exit(ft_fprintf(2, "Usage: ./asm <file name> (*.s)\n"));
	if (err == INVALID_NAME_COMMENT)
		exit(ft_fprintf(2, "Incorrect name or comment of champ\n"));
}