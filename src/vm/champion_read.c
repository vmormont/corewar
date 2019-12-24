/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:35:34 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/24 13:56:26 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_error	read_champion_from_file(int fd, t_header *head, char *code)
{
	if ((unsigned long)read(fd, (void*)head, sizeof(int) + PROG_NAME_LENGTH)\
	< (PROG_NAME_LENGTH + sizeof(int)))
		return (HEAD_SIZE_ERROR);
	head->magic = reverse_bits(head->magic, 1);
	lseek(fd, sizeof(int), SEEK_CUR);
	if (((unsigned long)read(fd, &head->prog_size, sizeof(int)\
	+ COMMENT_LENGTH)) < (sizeof(int) + COMMENT_LENGTH))
		return (HEAD_SIZE_ERROR);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((head->prog_size = reverse_bits(head->prog_size, 1)) > CHAMP_MAX_SIZE)
		return (EXEC_SIZE_ERROR);
	if ((unsigned long)read(fd, code, head->prog_size) < head->prog_size)
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
	error = read_champion_from_file(fd, &header, code);
	if (error)
		ft_exit_read(error, filename, &champs, header.prog_size);
	if (header.magic != COREWAR_EXEC_MAGIC)
		ft_exit_read(EXEC_CODE_ERROR, filename, &champs, NONE);
	if (!(champ = create_new_champ(&header, (void*)code)))
		ft_exit_read(MALLOC_FAILURE, filename, &champs, NONE);
	close(fd);
	return (champ);
}

static void		add_n_champion(char **av, t_champ **champs, int i)
{
	int		id;
	t_champ	*temp;

	temp = NULL;
	id = 0;
	if (av[i] && isdigit_word(av[i]))
	{
		if ((id = ft_atoi(av[i])) < 1 || id > MAX_PLAYERS)
			ft_exit_read(USAGE, NULL, champs, NONE);
		if (av[++i])
		{
			if (!is_filename_extension(av[i], ".cor"))
				ft_exit_read(FILE_EXTENSION_ERROR, NULL, champs, NONE);
		}
	}
	else
		ft_exit_read(USAGE, NULL, champs, NONE);
	if (id && id < USAGE)
		temp = get_champion_from_file(*champs, av[i]);
	else
		ft_exit_read(id, av[i], champs, NONE);
	add_champion2end(champs, temp, id);
}

void			read_champions_from_args(int ac, char **av, t_champ **champs)
{
	int		i;
	t_champ	*temp;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			add_n_champion(av, champs, i + 1);
			i = i + 2;
		}
		else if (is_filename_extension(av[i], ".cor"))
		{
			temp = get_champion_from_file(*champs, av[i]);
			add_champion2end(champs, temp, NONE);
		}
		else if (av[i][0] != '-' && !isdigit_word(av[i]))
			ft_exit_read(FILE_EXTENSION_ERROR, av[i], champs, NONE);
		++i;
	}
	sort_and_check_champs(*champs);
}

void			introduce(t_champ *champ)
{
	ft_printf("Introducing contestants...\n");
	while (champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
		ft_abs(champ->id), champ->code_size, champ->name, champ->comment);
		champ = champ->next;
	}
}
