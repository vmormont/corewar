/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:46:25 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/14 21:32:24 by astripeb         ###   ########.fr       */
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

char		*get_clean_data_from_file(t_champ *champ, char *filename)
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

int			skip_spaces(char *filedata, int index)
{
	while (ft_isspace(filedata[index]) && filedata[index] != '\n')
		++index;
	return (index);
}

int			skip_spaces2next_line(char *filedata, int index)
{
	while (ft_isspace(filedata[index]))
	{
		if (filedata[index] == '\n')
		{
			++index;
			break ;
		}
		++index;
	}
	return (index);
}