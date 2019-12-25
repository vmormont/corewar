/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:38:31 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/25 17:49:53 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

char				*get_s_filename(char *arg)
{
	char			*tmp;
	char			*new;

	tmp = ft_strsub(arg, START, ft_strlen(arg) - EXTENSION);
	new = ft_strjoin(tmp, ".s");
	free(tmp);
	return (new);
}

char				get_num_type(char num, int num_arg)
{
	return ((num >> (num_arg * 2)) & 3);
}

int					get_num(int fd, size_t t_size, char type)
{
	unsigned char	buff[t_size];
	int				num;
	size_t			i;

	num = 0;
	i = 0;
	ft_bzero((void *)buff, t_size);
	if (read(fd, buff, t_size) < 0)
		exit(1);
	while (i < t_size)
	{
		num = ((num << (BYTE_SIZE)) | buff[(t_size - 1) - i]);
		i++;
	}
	num = reverse_bits(num, t_size / 4);
	if (type == IND_CODE)
		num = (short)num;
	return (num);
}

int					reverse_bits(int num, char full_bit)
{
	int				rev_num;

	if (full_bit)
	{
		rev_num = (num & 0xFF) << 24;
		rev_num = rev_num | ((num >> 8) & 0xFF) << 16;
		rev_num = rev_num | ((num >> 16) & 0xFF) << 8;
		rev_num = rev_num | ((num >> 24) & 0xFF);
	}
	else
	{
		rev_num = (num & 0xFF) << 8;
		rev_num = rev_num | ((num & 0xFF00) >> 8);
	}
	return (rev_num);
}

bool				is_filename_extension(char *filename, char *extension)
{
	filename = ft_strrchr(filename, '.');
	if (filename)
	{
		if (!ft_strcmp(filename, extension))
			return (true);
	}
	return (false);
}
