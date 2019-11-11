/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:45:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/11 23:55:25 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		parse_name(t_champ *champ, char **filedata)
{
	char	**words;
	char	*tmp_word;
	int		i;

	i = -1;
	while (*filedata[++i] && (!champ->name || !champ->comment))
	{
		words = ft_strsplit((const char*)filedata[i], '"');
		tmp_word = ft_strtrim(words[0]);
		if (!ft_strcmp(tmp_word, NAME_CMD_STRING))
			champ->name = ft_strdup(words[1]);
		else if (!ft_strcmp(tmp_word, COMMENT_CMD_STRING))
			champ->comment = ft_strdup(words[1]);
		else
			break ;
	}
	if (!champ->name || !champ->comment)
		lexical_error(&champ, NAME_ERROR, i, 0);
	return ;
}

void		lexical_analizer(t_champ *champ, char *filedata)
{
	char	**split;

	if (!(split = ft_strsplit(filedata, '\n')))
		ft_exit(&champ, MALLOC_FAILURE);
	parse_name(champ, split);
	ft_printf("%s\n%s\n", champ->name, champ->comment);
}

