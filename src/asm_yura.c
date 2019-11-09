/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_yura.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:04:09 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/09 17:29:12 by pcredibl         ###   ########.fr       */
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

void			create_cor_file(char *src_file)
{
	int			fd;
	char		*file_type;
	char		*file_name;
	char		*cor_file;

	if ((fd = open(src_file, O_RDONLY) < 0))
	{
		ft_printf("File %s can not to be opened\n", src_file);
		//perror("Error");
		return;
	}
	close(fd);
	if ((file_type = ft_strlstr(src_file, ".s", ft_strlen(src_file) - 1)) && ft_strlen(file_type) == 2)
	{
		//ft_printf("file type = %s\n", file_type);
		file_name = (char*)malloc(sizeof(char) * (ft_strlen(src_file) - 1));
		file_name = ft_strncpy(file_name, src_file, ft_strlen(src_file) - 2);
		file_name[ft_strlen(src_file) - 2] = '\0';
		//ft_printf("src file = %s, file name = %s\n", src_file, file_name);
		cor_file = ft_strjoin_f(file_name, ".cor");
		//ft_printf("cor file = %s\n", cor_file);
		fd = open(cor_file, O_CREAT | O_EXCL | O_WRONLY);
		free(cor_file);
		close(fd);
	}
	else
		ft_printf("File %s have invalid type\n", src_file);
}