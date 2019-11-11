/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:45:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/11 16:44:50 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		clean_commetns(char *data)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	while (data[i])
	{
		if (data[i] == '"')
			in = in ? 0 : 1;
		if (!in && (data[i] == COMMENT_CHAR || data[i] == ALT_COMMENT_CHAR))
		{
			while (data[i] && data[i] != '\n')
				data[i++] = ' ';
		}
		++i;
	}
	return (0);
}


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
		if (tmp_word[0] != COMMENT_CHAR && tmp_word[0] != ALT_COMMENT_CHAR)
		{
			if (!ft_strcmp(tmp_word, ".name"))
				champ->name = ft_strdup(words[1]);
			else if (!ft_strcmp(tmp_word, ".comment"))
				champ->comment = ft_strdup(words[1]);
			else
			 break ;
		}
	}
	if (!champ->name || !champ->comment)
	{
		free_champ(&champ);
		ft_exit(INVALID_NAME_COMMENT);
	}
	return ;
}

/*int		add_name_comment(t_champ *champ, char **filedata)
{
	int i;
	i = 0;
	//разбиваем строку по
	while (filedata[i] && (!champ->name || !champ->comment))
	{
		if (ft_strstr(filedata[i], NAME_CMD_STRING))
		{

		}
		else if (ft_strstr(filedata[i], COMMENT_CMD_STRING))
		{

		}
		++i;
	}
	return (0);
}*/

t_champ		*lexical_analizer(t_champ *champ, char *filedata)
{
	char	**split;

	//разбиваем считанную
	if (!(split = ft_strsplit(filedata, '\n')))
		return (0);
	parse_name(champ, split);
	return (0);
}

