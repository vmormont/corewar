/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:29:02 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/10 23:12:56 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op	g_op_tab[];

int				get_num_byte(char type, char t_dir_size)
{
	if (type == REG_CODE)
		return (1);
	else if (type == IND_CODE)
		return (2);
	else if (type == DIR_CODE && t_dir_size)
		return (2);
	else if (type == DIR_CODE && !t_dir_size)
		return (4);
	return (0);
}


int				instruct_len(char *instuct)
{
	char		type;
	char		ind;
	int			i;
	int			len;

	i = 0;
	ind = instuct[0];
	len = g_op_tab[ind].code_args ? 2 : 1;
	while (i < g_op_tab[ind].num_args)
	{
		type = get_arg_type_dasm(ind, instuct, i);
		len += get_num_byte(type, g_op_tab[ind].tdir_size);
		++i;
	}
	return (len);
}

int				create_s_file(char *name)
{
	char		*new;
	int			fd;

	fd = 0;
	new = ft_strsub(name, 0, ft_strlen(name) - 4);
	new = ft_strjoin(new, ".s");
	if (!(fd = open(new, O_RDWR
			| O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)))
		exit(EXIT_FAILURE);
	return (fd);
}

char			get_arg_type_dasm(char ind, char *code, int index)
{
	if (g_op_tab[ind].code_args)
		return ((code[1] >> (2 * (3 - index))) & 3);
	if (g_op_tab[ind].args[index] == D)
		return (DIR_CODE);
	if (g_op_tab[ind].args[index] == R)
		return (REG_CODE);
	if (g_op_tab[ind].args[index] == DI)
		return (IND_CODE);
	if (g_op_tab[ind].args[index] == RD)
		return (DIR_CODE);
	if (g_op_tab[ind].args[index] == RI)
		return (IND_CODE);
	if (g_op_tab[ind].args[index] == RDI)
		return (DIR_CODE);
	return (0);
}