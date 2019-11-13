/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:18:41 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/13 23:15:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	clean_commetns(char *data)
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

static int	parse_name(t_champ *champ, char *data)
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

static char	*get_clean_data_from_file(t_champ *champ, char *filename)
{
	int		fd;
	char	*data;

	if ((fd = open(filename, O_RDONLY)) < 1)
		ft_exit(&champ, 0);
	if (!(data = read_from_file_to_var(fd)))
	{
		close(fd);
		ft_exit(&champ, MALLOC_FAILURE);
	}
	clean_commetns(data);
	close(fd);
	return (data);
}

void		lexical_analizer(t_champ *champ, char *filename)
{
	int		i;
	char	*filedata;

	filedata = get_clean_data_from_file(champ, filename);
	i = parse_name(champ, filedata);
	parse_instr(champ, filedata, i);
}
