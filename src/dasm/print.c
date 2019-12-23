/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:56:19 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/23 17:28:41 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op g_op_tab[];

void				print_name_comment_to_fd(char *name, char *comment,\
										int fd_out)
{
	ft_fprintf(fd_out, ".name \"%s\"\n", name);
	ft_fprintf(fd_out, ".comment \"%s\"\n\n", comment);
}

void				print_code_first(int fd, int fd_out)
{

	short			ind;
	char			code_args;
	int				num;
	int				i;
	int				arg_type;

	while (read(fd, &ind, 1) > 0)
	{
		if (!ind)
			continue;
		ft_fprintf(fd_out, "%s ", g_op_tab[ind].name);
		if (g_op_tab[ind].code_args)
		{
			if (read(fd, &code_args, 1) < 0)
				exit(EXIT_FAILURE);
			i = 6;
			while (i >= 8 - (2 * g_op_tab[ind].num_args))
			{
				arg_type = (code_args >> i) & 3;
				if (((code_args >> i) & 3) == REG_CODE)
				{
					num = get_num(fd, T_REG, REG_CODE);
					ft_fprintf(fd_out, "r%d", num);
				}
				else if (((code_args >> i) & 3) == IND_CODE)
				{
					num = get_num(fd, IND_SIZE, IND_CODE);
					ft_fprintf(fd_out, "%d", num);
				}
				else if (((code_args >> i) & 3) == DIR_CODE)
				{
					num = get_num(fd, g_op_tab[ind].tdir_size, DIR_CODE);
					ft_fprintf(fd_out, "%%%d", num);
				}
				i != 8 - (2 * g_op_tab[ind].num_args) ? ft_fprintf(fd_out, ", ") : 0;
				i -= 2;
			}
		}
		else
		{
			num = get_num(fd, g_op_tab[ind].tdir_size, DIR_CODE);
			ft_fprintf(fd_out, "%%%hd", num);
		}
		ft_fprintf(fd_out, "\n");
	}
}
