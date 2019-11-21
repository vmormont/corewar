/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:50:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/21 15:45:36 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

# define INVALID_HEAD_SIZE 305
# define EXEC_CODE_ERROR 306
# define EXEC_SIZE_ERROR 307

int		read_cor_file(char *filename);

typedef	struct s_champ
{
	char			*name;
	char			*comment;
	int				code_size;
	struct s_champ	*next;
}				t_champ;

static void	ft_exit_read(int err, char *filename, int fd, int exec_size)
{
	if (err == INVALID_HEAD_SIZE)
		ft_fprintf(2, "Error: File %s has a code size that %s\n",\
		filename, "differ from what its header says");
	else if (err == EXEC_CODE_ERROR)
		ft_fprintf(2, "Error: File %s has a code size that %s\n",\
		filename, "differ from what its header says");
	else if (err == EXEC_SIZE_ERROR)
		ft_fprintf(2, "Error: File %s has too large a code (%d bytes > %d%s",\
		filename, exec_size, CHAMP_MAX_SIZE, " bytes)\n");
	close(fd);
	exit(err);
}

static int		reverse_bits(int num, char full_bit)
{
	int		rev_num;
	int		i;

	i = 0;
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

int		read_cor_file(char *filename)
{
	t_header	header;
	int			fd;
	int			n;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_exit_read(0, filename, 0, 0);
	if (read(fd, (void*)&header, sizeof(header)) < sizeof(header))
		ft_exit_read(INVALID_HEAD_SIZE, filename, fd, 0);

	header.prog_size = reverse_bits(header.prog_size, 1);
	header.magic = reverse_bits(header.magic, 1);

	if (header.magic != COREWAR_EXEC_MAGIC)
		ft_exit_read(EXEC_CODE_ERROR, filename, fd, 0);
	if (header.prog_size > CHAMP_MAX_SIZE)
		ft_exit_read(EXEC_SIZE_ERROR, filename, fd, header.prog_size);

	ft_printf("magic     = %x\n", header.magic);
	ft_printf("name      = %s\n", header.prog_name);
	ft_printf("comment   = %s\n", header.comment);
	ft_printf("exec_size = %d\n", header.prog_size);
	close(fd);
	return (0);
}
