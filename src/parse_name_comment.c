/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:10:47 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/19 18:35:42 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	add_name(t_champ *champ, char *data, int i)
{
	int	j;

	i = skip_spaces(data, i);
	if (data[i++] != '"')
		error_manager(&champ, &data[--i], T_NONE);
	j = i;
	while (data[i] && data[i] != '"')
		++i;
	if (!champ->name)
	{
		if (!(champ->name = ft_strsub(data, j, i - j)))
			ft_exit(&champ, MALLOC_FAILURE);
	}
	else
		error_manager(&champ, &data[i], T_NAME);
	++i;
	i = skip_spaces(data, i);
	if (!data[i] || data[i++] != '\n')
		error_manager(&champ, &data[i], T_NONE);
	return (i);
}

static int	add_comment(t_champ *champ, char *data, int i)
{
	int	j;

	// пропускаем пробелы после ".comment"
	i = skip_spaces(data, i);
	// если не начало строки сообщаем об ошибке
	if (data[i++] != '"')
		error_manager(&champ, &data[--i], T_NONE);
	//запонимаем индекс начала
	j = i;
	//проходим все предложение в " "
	while (data[i] && data[i] != '"')
		++i;
	// в зависимости от флага добавляем имя или комментарий
	if (!champ->comment)
	{
		if (!(champ->comment = ft_strsub(data, j, i - j)))
			ft_exit(&champ, MALLOC_FAILURE);
	}
	else
		error_manager(&champ, &data[i], T_COMMENT);
	//переход на следущую строку
	i = skip_spaces(data, ++i);
	//если дошли до конца файла или не перешли на следующую строку
	//сообщаем об ошибке
	if (!data[i] || data[i++] != '\n')
		error_manager(&champ, &data[i], T_NONE);
	return (i);
}

int			parse_name(t_champ *champ, char *data)
{
	int i;

	i = 0;
	while (ft_isspace(data[i]))
		++i;
	while (data[i])
	{
		if (!ft_strncmp(&data[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			i = add_name(champ, data, i + ft_strlen(NAME_CMD_STRING));
		else if (!ft_strncmp(&data[i], COMMENT_CMD_STRING,\
		ft_strlen(COMMENT_CMD_STRING)))
			i = add_comment(champ, data, i + ft_strlen(COMMENT_CMD_STRING));
		else
			break ;
		while (ft_isspace(data[i]))
			++i;
	}
	if (!champ->name || !champ->comment)
		error_manager(&champ, &data[i], T_NONE);
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		ft_exit(&champ, NAME_LEN_ERROR);
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		ft_exit(&champ, COMMENT_LEN_ERROR);
	return (i);
}
