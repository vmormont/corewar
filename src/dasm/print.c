/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:56:19 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/21 17:02:22 by pcredibl         ###   ########.fr       */
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

	char			ind;
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
				;//ошибка;
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
			
		
/*		if (ind == LIVE)
			ft_fprintf(fd_out, "%%%d\n", get_num(fd, T_IND));
		else if (ind == LFORK || ind == FORK || ind == ZJMP)
			ft_fprintf(fd_out, "%%%hd\n", get_num(fd, T_DIR));
		else if (ind == AFF)
			ft_fprintf(fd_out, "r%hhu\n", get_num(fd, T_REG));
		else
			print_code_continiue(ind, get_num(fd, T_REG), fd, fd_out);
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
			ft_fprintf(fd_out, "r%hhu", get_num(fd, T_REG));
		else if (num_type == IND_DASM)
			ft_fprintf(fd_out, "%d", get_num(fd, T_DIR));
		else if (opcode == STI || opcode == LDI || opcode == LLDI)
			ft_fprintf(fd_out, "%%%hd", get_num(fd, T_DIR));
		else if (num_type)
			ft_fprintf(fd_out, "%%%d", get_num(fd, T_IND));
		--num_arg;
		num_type = get_num_type(num, num_arg);
		if (num_type)
			ft_fprintf(fd_out, ", ");
		else
			ft_fprintf(fd_out, "\n");
	}
}*/
