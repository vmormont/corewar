/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:45:23 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/10 22:17:33 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op	g_op_tab[];

void			disassemble(t_champ *champs, char **argv)
{
	t_champ		*tmp;
	int			fd;
	int			count;

	count = 1;
	fd = 0;
	tmp = champs;
	while (tmp)
	{
		fd = create_s_file(argv[count]);
		write_name_comment_to_fd(tmp->name, tmp->comment, fd);
		write_code_to_fd(tmp->code, tmp->code_size, fd);
		close(fd);
		tmp = tmp->next;
	}
}
