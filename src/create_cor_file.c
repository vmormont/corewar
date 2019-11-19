/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:04:09 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/19 20:54:29 by astripeb         ###   ########.fr       */
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

void			create_cor_file(char *src_file, t_champ *champ)
{
	int			fd;
	char		*file_type;
	char		*file_name;
	char		*cor_file;

	if ((file_type = ft_strlstr(src_file, ".s", ft_strlen(src_file) - 1)) && ft_strlen(file_type) == 2)
	{
		//ft_printf("file type = %s\n", file_type);
		file_name = (char*)malloc(sizeof(char) * (ft_strlen(src_file) - 1));
		file_name = ft_strncpy(file_name, src_file, ft_strlen(src_file) - 2);
		file_name[ft_strlen(src_file) - 2] = '\0';
		//ft_printf("src file = %s, file name = %s\n", src_file, file_name);
		cor_file = ft_strjoin_f(file_name, ".cor");
		//ft_printf("cor file = %s\n", cor_file);
//		fd = open(src_file, O_RDONLY);
		if ((fd = open(cor_file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
			ft_exit(&champ, ERROR_OF_OPEN_FILE);
		free(cor_file);
		write_champ_in_file(fd, champ);
		close(fd);
	}
	else
		ft_fprintf(2, "File %s have invalid type\n", src_file);
}
