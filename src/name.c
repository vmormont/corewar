/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:45:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/09 17:45:43 by astripeb         ###   ########.fr       */
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

/*
int		parse_name(t_champ *champ, char **filedata, int i)
{
	char	**name_str;

	if (!(name_str = ft_strsplit()))
}

int		add_name_comment(t_champ *champ, char **filedata)
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
}

int		lexical_analizer(t_champ *champ, char *filedata)
{
	char	**split;

	//разбиваем считанную
	if (!(split = ft_strsplit(filedata, '\n')))
		return (0);
	parse_name(champ, split);
	return (0);
}
*/
