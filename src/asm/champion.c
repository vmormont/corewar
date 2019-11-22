/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:52:36 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 10:34:10 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	clean_commetns(char *data)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	while (data[i])
	{
		if (data[i] == '"')
			in = in ? 0 : 1;
		if (!in && (data[i] == COMMENT_CHAR || data[i] == ALT_COMMENT_CHAR))
		{
			while (data[i] && data[i] != '\n')
				data[i++] = ' ';
		}
		++i;
	}
	return (0);
}

char		*get_clean_data_from_file(t_champ *champ, char *filename)
{
	int		fd;
	char	*data;

	if ((fd = open(filename, O_RDONLY)) < 1)
		ft_exit(&champ, 0);
	if (!(data = read_from_file_to_var(fd)))
	{
		close(fd);
		ft_exit(&champ, MALLOC_FAILURE);
	}
	clean_commetns(data);
	close(fd);
	return (data);
}

t_champ		*create_champ(void)
{
	t_champ	*champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero((void*)champ, sizeof(t_champ));
	return (champ);
}

void		free_champ(t_champ **champ)
{
	if (champ && *champ)
	{
		ft_strdel(&(*champ)->data);
		ft_strdel(&(*champ)->name);
		ft_strdel(&(*champ)->comment);
		del_instr(&(*champ)->instr);
		del_label(&(*champ)->labels);
		free(*champ);
		*champ = NULL;
	}
}

t_header	*create_head_of_champion(t_champ *champ)
{
	t_header	*head;
	t_instr		*instruct;

	if (!(head = (t_header*)malloc(sizeof(t_header))))
		ft_exit(&champ, MALLOC_FAILURE);
	ft_bzero((void*)head, sizeof(t_header));
	head->magic = reverse_bits(COREWAR_EXEC_MAGIC, 1);
	ft_memcpy((void*)head->prog_name, (const void*)champ->name,\
	ft_strlen(champ->name));
	ft_memcpy((void*)head->comment, (const void*)champ->comment,\
	ft_strlen(champ->comment));
	instruct = champ->instr;
	while (instruct->next)
		instruct = instruct->next;
	head->prog_size = instruct->offset + instruct->instr_size;
	return (head);
}
