/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:36:53 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/14 02:21:48 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void				ft_exit_dasm(char *identifier, int fd)
{
	ft_printf("{red}ERROR: ");
	ft_printf("{red}%s with file descriptor %i.\n", identifier, fd);
	exit(EXIT_FAILURE);
}

void				print_usage(void)
{
	ft_printf("{eoc}Welcome to Disassembler!\n");
	ft_printf("Start the program correctly:\n\n");
	ft_printf("./dasm [filename.cor]\n\n");
	ft_printf("Have a nice day, My Friend!\n");
}
