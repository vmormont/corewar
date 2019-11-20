/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 10:59:27 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_champ		*champ;
	int			fd_cor;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	asm_file_parser(champ, argv[1]);
	fd_cor = create_cor_file(argv[1], champ);
	write_champ_in_file(fd_cor, champ);
	free_champ(&champ);
	close(fd_cor);
	return (0);
}
