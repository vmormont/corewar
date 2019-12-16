/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:27:32 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/13 20:34:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_cor_filename(char *src_file, t_champ *champ)
{
	char		*cor_file;
	char		*file_type;

	cor_file = NULL;
	if (!(cor_file = ft_strnew(ft_strlen(src_file) + 2)))
		ft_exit(&champ, MALLOC_FAILURE);
	ft_strncpy(cor_file, src_file, ft_strlen(src_file) - 2);
	ft_strcpy(&cor_file[ft_strlen(src_file) - 2], ".cor");
	return (cor_file);
}

static void	write_args(int fd, t_instr *instr)
{
	int		i;

	i = 0;
	while (i < instr->num_args)
	{
		if (instr->args[i].type == T_DIR)
		{
			instr->args[i].value = reverse_bits(instr->args[i].value,\
			instr->tdir_size - 2);
			write(fd, (const void*)&instr->args[i].value, instr->tdir_size);
		}
		else if (instr->args[i].type == T_IND)
		{
			instr->args[i].value = reverse_bits(instr->args[i].value, 0);
			write(fd, (const void*)&instr->args[i].value, 2);
		}
		else if (instr->args[i].type == T_REG)
			write(fd, (const void*)&instr->args[i].value, 1);
		i++;
	}
}

static void	write_instr(int fd, t_instr *instr)
{
	char	code_args;

	while (instr)
	{
		write(fd, (const void*)&instr->code, 1);
		if (instr->code_args)
		{
			code_args = define_code_args(instr);
			write(fd, (const void*)&code_args, 1);
		}
		write_args(fd, instr);
		instr = instr->next;
	}
}

int			define_code_args(t_instr *instr)
{
	char	code;
	int		i;
	int		n;

	n = 6;
	i = 0;
	code = 0;
	while (i < instr->num_args)
	{
		if (instr->args[i].type == T_IND)
			code = code | (IND_CODE << n);
		else if (instr->args[i].type == T_REG)
			code = code | (REG_CODE << n);
		else if (instr->args[i].type == T_DIR)
			code = code | (DIR_CODE << n);
		n -= 2;
		++i;
	}
	return (code);
}

void		assembly(t_champ *champ, char *s_file)
{
	t_header	*header;
	char		*cor_file;
	int			fd;
	int			zero;

	zero = 0;
	cor_file = get_cor_filename(s_file, champ);
	if ((fd = open(cor_file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
	{
		ft_strdel(&cor_file);
		ft_exit(&champ, 0);
	}
	header = create_head_of_champion(champ);
	header->prog_size = reverse_bits(header->prog_size, 1);
	write(fd, (void*)&header->magic, sizeof(unsigned int));
	write(fd, (void*)&header->prog_name, PROG_NAME_LENGTH);
	write(fd, (void*)&zero, 4);
	write(fd, (void*)&header->prog_size, 4);
	write(fd, (void*)&header->comment, COMMENT_LENGTH);
	write(fd, (void*)&zero, 4);
	write_instr(fd, champ->instr);
	ft_printf("Writing output program to %s\n", cor_file);
	ft_memdel((void*)&header);
	ft_strdel(&cor_file);
	close(fd);
}
