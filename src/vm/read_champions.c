/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:40:44 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/25 14:37:49 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_error	read_one_champion_from_file(int fd, char *filename,\
				t_header *head, char *code)
{
	if (read(fd, (void*)head, sizeof(int) + PROG_NAME_LENGTH)\
	< (PROG_NAME_LENGTH + sizeof(int)))
		return (HEAD_SIZE_ERROR);
	head->magic = reverse_bits(head->magic, 1);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((read(fd, &head->prog_size, sizeof(int) + COMMENT_LENGTH))\
	< (sizeof(int) + COMMENT_LENGTH))
		return (HEAD_SIZE_ERROR);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((head->prog_size = reverse_bits(head->prog_size, 1)) > CHAMP_MAX_SIZE)
		return (EXEC_SIZE_ERROR);
	if (read(fd, code, head->prog_size) < head->prog_size)
		return (CODE_SIZE_ERROR);
	return (NONE);
}

static t_champ	*get_champion_from_file(t_champ *champs, char *filename)
{
	int			fd;
	char		code[CHAMP_MAX_SIZE + 1];
	t_header	header;
	t_champ		*champ;
	t_error		error;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_exit_read(NONE, filename, &champs, NONE);
	ft_bzero((void*)&header, sizeof(t_header));
	ft_bzero((void*)&code, CHAMP_MAX_SIZE);
	error = read_one_champion_from_file(fd, filename, &header, (char*)&code);
	if (error)
		ft_exit_read(error, filename, &champs, header.prog_size);
	if (header.magic != COREWAR_EXEC_MAGIC)
		ft_exit_read(EXEC_CODE_ERROR, filename, &champs, NONE);
	if (!(champ = create_new_champ(&header, (void*)code)))
		ft_exit_read(MALLOC_FAILURE, filename, &champs, NONE);
	close(fd);
	return (champ);
}

static int		valid_n_argument(char **av)
{
	int 	id;
	char	*file_type;

	id = 0;
	if (!*av)
		return (USAGE);
	if (isdigit_word(*av))
	{
		if ((id = ft_atoi(*av)) < 1 || id > MAX_PLAYERS)
			return (USAGE);
		av++;
		if (*av)
		{
			if (!is_filename_extension(*av, ".cor"))
				return (FILE_EXTENSION_ERROR);
		}
		else
			return(ARG_OPTION_ERROR);
	}
	return (id);
}

static void		add_n_champion(int ac, char **av, t_champ **champs, int index)
{
	int 	id;
	t_champ *temp;

	if (index >= ac)
		ft_exit_read(USAGE, NULL, champs, NONE);
	id = valid_n_argument(&av[index]);
	if (id && id < USAGE)
		temp = get_champion_from_file(*champs, av[++index]);
	else
		ft_exit_read(id, av[index], champs, NONE);
	insert_champion(champs, temp, id);
}

t_champ			*read_champions_from_args(int ac, char **av)
{
	int		i;
	int		n_champ;
	t_champ	*temp;
	t_champ	*champs;

	i = 1;
	champs = NULL;
	n_champ	 = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			n_champ ? ft_exit_read(USAGE, NULL, &champs, NONE) : NONE;
			n_champ = i + 1;
			i += 2;
		}
		else if (is_filename_extension(av[i], ".cor"))
		{
			temp = get_champion_from_file(champs, av[i]);
			add_champion2end(&champs, temp);
		}
		else if (av[i][0] != '-' && !isdigit_word(av[i]))
			ft_exit_read(FILE_EXTENSION_ERROR, av[i], &champs, NONE);
		++i;
	}
	n_champ ? add_n_champion(ac, av, &champs, n_champ) : NONE;
	return (champs);
}
