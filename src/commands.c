/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:24:27 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/14 18:11:32 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		skip_spaces(char *filedata, int index)
{
	while (ft_isspace(filedata[index] && filedata[index] != '\n'))
		++index;
	return (index);
}


static int	offset4label(t_instr *instr)
{
	int offset;

	offset = 0;
	while (instr)
	{
		offset += instr->instr_size;
		instr = instr->next;
	}
	return (offset);
}

static int	ft_islabel(char c, char *label_chars)
{
	int i;

	i = 0;
	while (label_chars[i])
	{
		if (c == label_chars[i])
			return(1);
		++i;
	}
	return (0);
}

int			detect_label(t_champ *champ, char *filedata, int i)
{
	int		j;
	char	*name;

	// пропускаем пробельные символы
	while (ft_isspace(filedata[i]))
		++i;
	// запоминаем начало символов в строке
	j = i;
	// проверяем является ли началом строки лейбл
	while (ft_islabel(filedata[i], LABEL_CHARS))
		++i;
	// добавляем лейбл
	if (filedata[i] == LABEL_CHAR)
	{
		if (!(name = ft_strsub(filedata, j, i - j)))
			ft_exit(&champ, MALLOC_FAILURE);
		champ->labels = add_label2end(champ->labels, name,\
		offset4label(champ->instr));
		if (!champ->labels)
			ft_exit(&champ, MALLOC_FAILURE);
		++i;
	}
	// возвращаем цикл
	else
		i = j;
	return (i);
}
