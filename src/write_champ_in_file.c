/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ_in_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:27:32 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/19 20:27:20 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void write_args(int fd, t_instr *instr)
{
	int		i;

	i = 0;
	while (instr->args[i].type)
	{
		if (instr->args[i].type == T_DIR)
			write(fd, (const void*)&instr->args[i].value, instr->tdir_size);
		else if (instr->args[i].type == T_IND)
			write(fd, (const void*)&instr->args[i].value, 2);
		else if (instr->args[i].type == T_REG)
			write(fd, (const void*)&instr->args[i].value, 1);
		i++;
	}
}

static void write_instr(int fd, t_instr *instr)
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

void		write_champ_in_file(int fd, t_champ *champ)
{
	char	*code;
	t_header	*header;
	int			instr_size;

	header = create_header();
	copy2_head(champ, header);
	/*ft_printf("magic = %u\n", header->magic);
	ft_printf("name = %s\n", header->prog_name);
	ft_printf("size = %u\n", header->prog_size);
	ft_printf("comment = %s\n", header->comment);*/
	write(fd, (void*)&header->magic, sizeof(unsigned int));
	write(fd, (void*)&header->prog_name, PROG_NAME_LENGTH + 4);
	//write(fd, (void*)"Hello", 5);
	instr_size = reverse_bits(size_instr(champ->instr), 1);
	write(fd, (void*)&instr_size, 4);
	write(fd, (void*)&header->comment, COMMENT_LENGTH + 4);
	write_instr(fd, champ->instr);
}