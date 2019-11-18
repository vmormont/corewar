/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ_in_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:27:32 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/18 17:55:00 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	size_instr(t_instr *instr)
{
	int		size;

	while (instr->next)
		instr = instr->next;
	size = instr->offset + instr->instr_size;
	ft_printf("size instr = %d\n", size);
	return (size);
}

static void	write_name_comment(t_champ *champ, char *code)
{
	int		i;

	ft_strcpy(code, "00ea83f3");
	code += 4;
	i = -1;
	while (++i < PROG_NAME_LENGTH)
	{
		code[i] = champ->name[i] ? champ->name[i] : 0;
	}
}

void		write_champ_in_file(int fd, t_champ *champ)
{
	char	*code;

	ft_fprintf(fd, "Champ name is %s\n", champ->name);
	code = (char*)malloc(16 + PROG_NAME_LENGTH + COMMENT_LENGTH + size_instr(champ->instr));
	write_name_comment(champ, code);
}