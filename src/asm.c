/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/09 13:03:44 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		create_cor_file(char *src_file)
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
	if ((file_type = ft_strstr((const char*)src_file, ".s")) && ft_strlen(file_type) == 2)
	{
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
	ft_printf("file type = %s\n", file_type);
}

int				main	(int argc, char **av)
{
	int			i;

	i = 0;
	if (argc == 1)
		ft_exit(USAGE);
	else
	{
		while (av[++i])
			create_cor_file(av[i]);
	}
	
	return (0);
}
