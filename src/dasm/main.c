/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:28:20 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/10 23:11:47 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static t_error	read_champ_from_file(int fd, char *filename, t_header *head, char *code)
{
	if (read(fd, (void *)head, sizeof(int) + PROG_NAME_LENGTH) < (sizeof(int) + PROG_NAME_LENGTH))
		return (HEAD_SIZE_ERROR);
	head->magic = reverse_bits(head->magic, 1);
	lseek(fd, sizeof(int), SEEK_CUR);
	if (read(fd, &head->prog_size, sizeof(int) + COMMENT_LENGTH) < (sizeof(int) + COMMENT_LENGTH))
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
	t_header	head;
	t_champ		*new;
	t_error		error;

	if ((fd = open(filename, O_RDONLY)) <= 0)
		ft_exit_read(NONE, filename, &champs, NONE);
	ft_bzero((void *)&head, sizeof(t_header));
	ft_bzero((void *)&code, CHAMP_MAX_SIZE);
	error = read_champ_from_file(fd, filename, &head, (char *)&code);
	close(fd);
	if (error)
		ft_exit_read(error, filename, &champs, head.prog_size);
	if (head.magic != COREWAR_EXEC_MAGIC)
		ft_exit_read(EXEC_CODE_ERROR, filename, &champs, NONE);
	if (!(new = create_new_champ(&head, (void *)code)))
		ft_exit_read(MALLOC_FAILURE, filename, &champs, NONE);
	return (new);
}

static void		read_cor_files_from_args(int argc, char **argv, t_champ **champs)
{
	int			count;
	t_champ		*tmp;

	count = 0;
	while (count < argc)
	{
		if (is_filename_extension(argv[count], ".cor"))
		{
			tmp = get_champion_from_file(*champs, argv[count]);
			add_champion2end(champs, tmp, NONE);
		}
		++count;
	}
	sort_and_check_champs(*champs);
}

int				main(int argc, char **argv)
{
	t_champ		*champs;

	read_cor_files_from_args(argc, argv, &champs);
	disassemble(champs, argv);
	free(champs);
	return (0);
}
