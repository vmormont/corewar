/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:35:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/21 21:01:28 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_champ	*create_new_champ(t_header *head, char *code)
{
	t_champ *champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero((void*)champ, sizeof(t_champ));
	if (!(champ->name = ft_strdup(head->prog_name))\
	|| !(champ->comment = ft_strdup(head->comment))\
	|| !(champ->code = ft_strnew(head->prog_size)))
	{
		del_one_champion(&champ);
		return (NULL);
	}
	ft_strncpy(champ->code, code, head->prog_size);
	champ->code_size = head->prog_size;
	champ->magic = head->magic;
	return (champ);
}

void			del_one_champion(t_champ **champ)
{
	if (champ && *champ)
	{
		(*champ)->next = NULL;
		ft_memdel((void*)champ);
		ft_memdel((void*)(*champ)->name);
		ft_memdel((void*)(*champ)->comment);
		ft_memdel((void*)(*champ)->code);
	}
}

void			del_champions(t_champ **begin)
{
	t_champ	*first;
	t_champ	*second;

	if (begin && *begin)
	{
		first = *begin;
		while (first)
		{
			second = first;
			first = first->next;
			del_one_champion(&second);
		}
		*begin = NULL;
	}
}

static void		ft_exit_read(int err, char *filename, int fd, int exec_size)
{
	if (err == MALLOC_FAILURE)
		ft_fprintf(2, "Error: Failed to alloc memory\n");
	else if (err == INVALID_HEAD_SIZE)
		ft_fprintf(2, "Error: File %s has a code size that %s\n",\
		filename, "differ from what its header says");
	else if (err == EXEC_CODE_ERROR)
		ft_fprintf(2, "Error: File %s has a code size that %s\n",\
		filename, "differ from what its header says");
	else if (err == EXEC_SIZE_ERROR)
		ft_fprintf(2, "Error: File %s has too large a code (%d bytes > %d%s",\
		filename, exec_size, CHAMP_MAX_SIZE, " bytes)\n");
	else if (err == CODE_SIZE_ERROR)
		ft_fprintf(2, "Error: File %s size of code is incorrect\n", filename);
	close(fd);
	exit(err);
}

static void		read_champion_from_file(int fd, char *filename,\
				t_header *head, char *code)
{
	if (read(fd, (void*)head, sizeof(int) + PROG_NAME_LENGTH)\
	< (PROG_NAME_LENGTH + sizeof(int)))
		ft_exit_read(INVALID_HEAD_SIZE, filename, fd, 0);
	head->magic = reverse_bits(head->magic, 1);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((read(fd, &head->prog_size, sizeof(int) + COMMENT_LENGTH))\
	< (sizeof(int) + COMMENT_LENGTH))
		ft_exit_read(INVALID_HEAD_SIZE, filename, fd, 0);
	lseek(fd, sizeof(int), SEEK_CUR);
	head->prog_size = reverse_bits(head->prog_size, 1);
	if (read(fd, code, head->prog_size) != head->prog_size)
		ft_exit_read(CODE_SIZE_ERROR, filename, fd, 0);
	if (read(fd, code, head->prog_size))
		ft_exit_read(CODE_SIZE_ERROR, filename, fd, 0);
}

t_champ			*get_champion_from_file(char *filename)
{
	int			fd;
	char		code[CHAMP_MAX_SIZE];
	t_header	header;
	t_champ		*champ;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_exit_read(0, filename, 0, 0);
	ft_bzero((void*)&header, sizeof(t_header));
	ft_bzero((void*)&code, CHAMP_MAX_SIZE);
	read_champion_from_file(fd, filename, &header, (char*)&code);
	if (header.magic != COREWAR_EXEC_MAGIC)
		ft_exit_read(EXEC_CODE_ERROR, filename, fd, 0);
	if (!(champ = create_new_champ(&header, code)))
		return (NULL);
	ft_printf("magic     = %x\n", champ->magic);
	ft_printf("name      = %s\n", champ->name);
	ft_printf("comment   = %s\n", champ->comment);
	ft_printf("exec_size = %d\n", champ->code_size);
	close(fd);
	return (champ);
}

void			add_champion2end(t_champ **begin, t_champ *champ)
{
	t_champ	*temp;

	if (begin)
	{
		if (!*begin)
		{
			*begin = champ;
			champ->id = 1;
		}
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = champ;
			champ->id = temp->id + 1;
		}
	}
}
