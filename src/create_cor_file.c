/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:04:09 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 10:40:52 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_strlstr(char *src, char *pattern, int len)
{
	int			i;

	len -= (ft_strlen(pattern) - 1);
	while (len >= 0)
	{
		if (src[len] == pattern[0])
		{
			i = 1;
			while ((src[len + i] == pattern[i]) && pattern[i])
				++i;
			if (!pattern[i])
				return (src + len);
		}
		len--;
	}
	return (NULL);
}

int				create_cor_file(char *src_file, t_champ *champ)
{
	int			fd;
	char		*cor_file;
	char		*file_type;

	fd = 0;
	if ((file_type = ft_strlstr(src_file, ".s", ft_strlen(src_file) - 1))\
	&& ft_strlen(file_type) == 2)
	{
		if (!(cor_file = ft_strnew(ft_strlen(src_file) + 2)))
			ft_exit(&champ, MALLOC_FAILURE);
		ft_strncpy(cor_file, src_file, ft_strlen(src_file) - 2);
		ft_strcpy(&cor_file[ft_strlen(src_file) - 2], ".cor");
		if ((fd = open(cor_file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		{
			ft_strdel(&cor_file);
			ft_exit(&champ, 0);
		}
		ft_strdel(&cor_file);
	}
	else
		ft_exit(&champ, INVALID_FILE_NAME);
	return (fd);
}
