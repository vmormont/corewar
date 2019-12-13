/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:56:19 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/14 02:26:10 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op g_op_tab[];

void				print_name_comment_to_fd(char *name, char *comment,\
										int fd_out)
{
	ft_printf_fd(".name \"%s\"\n", fd_out, name);
	ft_printf_fd(".comment \"%s\"\n\n", fd_out, comment);
}

void				print_code_first(int fd, int fd_out)
{
	char			ind;

	while (read(fd, &ind, 1) > 0)
	{
		if (!ind)
			continue;
		ft_printf_fd("%s ", fd_out, g_op_tab[ind].name);
		if (ind == LIVE)
			ft_printf_fd("%%%d\n", fd_out, get_num(fd, T_IND));
		else if (ind == LFORK || ind == FORK || ind == ZJMP)
			ft_printf_fd("%%%hd\n", fd_out, get_num(fd, T_DIR));
		else if (ind == AFF)
			ft_printf_fd("r%hhu\n", fd_out, get_num(fd, T_REG));
		else
			print_code_continiue(ind, get_num(fd, T_REG),\
								fd, fd_out);
	}
}

void				print_code_continiue(int opcode, char num,\
										int fd, int fd_out)
{
	char			num_type;
	int				num_arg;

	num_arg = NUM_ARG;
	num_type = get_num_type(num, num_arg);
	while (num_type)
	{
		if (num_type == REG_DASM)
			ft_printf_fd("r%hhu", fd_out, get_num(fd, T_REG));
		else if (num_type == IND_DASM)
			ft_printf_fd("%d", fd_out, get_num(fd, T_DIR));
		else if (opcode == STI || opcode == LDI || opcode == LLDI)
			ft_printf_fd("%%%hd", fd_out, get_num(fd, T_DIR));
		else if (num_type)
			ft_printf_fd("%%%d", fd_out, get_num(fd, T_IND));
		--num_arg;
		num_type = get_num_type(num, num_arg);
		if (num_type)
			ft_printf_fd(", ", fd_out);
		else
			ft_printf_fd("\n", fd_out);
	}
}
