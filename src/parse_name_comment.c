/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:10:47 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/14 21:13:53 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	add_name_comment(t_champ *champ, char *data, int *i, char f)
{
	int	j;
	// пропускаем пробелы после ".name" или ".comment"
	while (ft_isspace(data[*i]))
		*i += 1;

	// если не начало строки сообщаем об ошибке
	if (data[(*i)++] != '"')
	lexical_error(&champ, data, &data[--*i]);

	//запонимаем индекс начала
	j = *i;
	//проходим все предложение в " "
	while (data[*i] && data[*i] != '"')
		++(*i);
	// в зависимости от флага добавляем имя или комментарий
	if (f)
		!(champ->name = ft_strsub(data, j, *i - j)) ?\
			ft_exit(&champ, MALLOC_FAILURE) : 0;
	else
		!(champ->comment = ft_strsub(data, j, *i -j)) ?\
			ft_exit(&champ, MALLOC_FAILURE) : 0;
	++(*i);
	//переход на следущую строку
	while (ft_isspace(data[*i]) && data[*i] != '\n')
		++(*i);
	//если дошли до конца файла или не перешли на следующую строку
	//сообщаем об ошибке
	if (!data[*i] || data[(*i)++] != '\n')
		lexical_error(&champ, data, &data[--(*i)]);
}

int			parse_name(t_champ *champ, char *data)
{
	int i;

	i = 0;
	while (ft_isspace(data[i]))
		++i;
	while(data[i] && (!champ->name || !champ->comment))
	{
		if(!ft_strncmp(&data[i], NAME_CMD_STRING,\
		ft_strlen(NAME_CMD_STRING)))
		{
			i += ft_strlen(NAME_CMD_STRING);
			add_name_comment(champ, data, &i, 1);
		}
		else if (!ft_strncmp(&data[i], COMMENT_CMD_STRING,\
		ft_strlen(COMMENT_CMD_STRING)))
		{
			i += ft_strlen(COMMENT_CMD_STRING);
			add_name_comment(champ, data, &i, 0);
		}
		else
			lexical_error(&champ, data, &data[i]);
		while (ft_isspace(data[i]))
			++i;
	}
	return (i);
}
