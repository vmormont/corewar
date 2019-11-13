/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:24:27 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/13 23:14:34 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	offset4label(t_instr *instr)
{
	int offset;

	offset = 0;
	while (instr)
	{
		offset =+ instr->instr_size;
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
			break ;
		++i;
	}
	if (!label_chars[i])
		return (0);
	return(1);
}

static int	detect_label(t_champ *champ, char *filedata, int i)
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

void		parse_instr(t_champ *champ, char *filedata, int i)
{
	int j;

	j = 0;
	while (filedata[i])
	{
		// вначале цикла мы находимся всегда вначале строки

		// так как лейблов подряд может быть несколько
		// мы добавляем их все
		while (j != i)
		{
			j = i;
			i = detect_label(champ, filedata, i);
		}

		//тут должна быть функция парсинга инструкции
		while (filedata[i] != '\n')
			++i;

		//переходим по пробельным символам на следующую строку
		while (ft_isspace(filedata[i]) && filedata[i] != '\n')
			++i;
		++i;
	}
	while (champ->labels)
	{
		ft_printf("label = %s, offset = %u\n",\
		champ->labels->name, champ->labels->offset);
		champ->labels = champ->labels->next;
	}
}
