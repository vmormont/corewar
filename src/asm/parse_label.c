/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:24:27 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/27 19:12:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

t_bool		islabelchar(char c, char *label_chars)
{
	int i;

	i = 0;
	while (label_chars[i])
	{
		if (c == label_chars[i])
			return (TRUE);
		++i;
	}
	return (FALSE);
}

int			islabel(char *data)
{
	int i;

	i = 0;
	while (islabelchar(data[i], LABEL_CHARS))
		++i;
	if (data[i] == LABEL_CHAR)
		return (i);
	return (0);
}

int			parse_label(t_champ *champ, char *filedata, int i)
{
	int		valid_label;
	t_label	*label;

	valid_label = 1;
	while (valid_label)
	{
		valid_label = islabel(&filedata[i]);
		if (valid_label)
		{
			if (!(label = new_label(offset4label(champ->instr))))
				ft_exit(&champ, MALLOC_FAILURE);
			if (!(label->name = ft_strsub(filedata, i, valid_label)))
			{
				del_one_label(&label);
				ft_exit(&champ, MALLOC_FAILURE);
			}
			i = i + valid_label + 1;
			add_label2end(&champ->labels, label);
			while (ft_isspace(filedata[i]))
				++i;
		}
	}
	return (i);
}
