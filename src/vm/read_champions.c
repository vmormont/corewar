/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:40:44 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 21:02:35 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_error	read_one_champion_from_file(int fd, char *filename,\
				t_header *head, char *code)
{
	if (read(fd, (void*)head, sizeof(int) + PROG_NAME_LENGTH)\
	< (PROG_NAME_LENGTH + sizeof(int)))
		return (INVALID_HEAD_SIZE);
	head->magic = reverse_bits(head->magic, 1);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((read(fd, &head->prog_size, sizeof(int) + COMMENT_LENGTH))\
	< (sizeof(int) + COMMENT_LENGTH))
		return (INVALID_HEAD_SIZE);
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
		ft_exit_read(NONE, filename, NONE, NONE);
	ft_bzero((void*)&header, sizeof(t_header));
	ft_bzero((void*)&code, CHAMP_MAX_SIZE);
	error = read_one_champion_from_file(fd, filename, &header, (char*)&code);
	if (error)
	{
		del_champions(&champs);
		ft_exit_read(error, filename, fd, header.prog_size);
	}
	if (header.magic != COREWAR_EXEC_MAGIC)
	{
		del_champions(&champs);
		ft_exit_read(EXEC_CODE_ERROR, filename, fd, NONE);
	}
	champ = create_new_champ(&header, (void*)code);
	close(fd);
	return (champ);
}

static int		valid_n_argument(char **av)
{
	int id;

	id = 0;
	if (isdigit_word(*av))
	{
		if ((id = ft_atoi(*av)) < 1 || id > MAX_PLAYERS)
			return (USAGE);
		av++;
		if (av && ft_strstr(*av, ".cor"))
			return (FILETYPE_ERROR);
	}
	return (id);
}

t_champ			*read_champions_from_args(int ac, char **av)
{
	int		i;
	int		id;
	t_champ	*temp;
	t_champ	*champs;

	i = 1;
	champs = NULL;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			id = valid_n_argument(&av[++i]);
			if (id && id < USAGE)
				temp = get_champion_from_file(champs, av[++i]);
			else
			{
				del_champions(&champs);
				ft_exit_read(MALLOC_FAILURE, av[i], NONE, NONE);
			}
		}
		else if (ft_strstr(av[i], ".cor"))
			temp = get_champion_from_file(champs, av[i]);
		if (!temp)
		{
			del_champions(&champs);
			ft_exit_read(MALLOC_FAILURE, av[i], NONE, NONE);
		}
		add_champion2end(&champs, temp);
		++i;
	}
	return (champs);
}
