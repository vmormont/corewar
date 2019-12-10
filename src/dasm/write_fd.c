/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:26:07 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/10 23:13:48 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op	g_op_tab[];

int				ft_printf_fd(const char *frm, int fd, ...)
{
	va_list			ap;
	t_modific		*mod;
	int				n;

	mod = NULL;
	mod = new_modific(mod, fd);
	va_start(ap, frm);
	n = 0;
	while (*frm)
	{
		n += *frm != '%' && *frm != '{' ? ft_putchar_fd(*frm, mod->fd) : 0;
		frm += *frm == '{' ? set_color(frm, &n, 1) : 0;
		if (*(frm + 1) != '\0')
			if (*frm == '%')
			{
				*++frm == 'n' ? count_print(va_arg(ap, long long int), n) : 0;
				frm += parsing_modific(frm, mod, ap);
				n += *frm && isspec(*++frm) ? pr_sp(ap, mod, *frm) :\
					pr_non_sp(mod, *frm);
			}
		frm++;
	}
	free(mod);
	va_end(ap);
	return (n);
}

void			write_type_to_fd(char type, char *code, int pos, int fd)
{
	char		ind;

	ind = code[0];
	if (type == REG_CODE)
		ft_printf_fd("r%hhu", fd, code[pos]);
	else if (type == IND_CODE)
		ft_printf_fd("%hd", fd, (short)(((short)code[pos] << 8) | (short)code[pos + 1]));
	else if (type == DIR_CODE && g_op_tab[ind].tdir_size)
		ft_printf_fd("%%%hd", fd, (int)(((short)code[pos] << 8) | (short)code[pos + 1]));
	else if (type == DIR_CODE)
		ft_printf_fd("%%%d", fd, (int)((int)code[pos + 3] | ((int)code[pos + 2] << 8) | ((int)code[pos + 1] << 16) | ((int)code[pos] << 24)));
}

int				write_instruction_to_fd(char *code, int fd)
{
	char		type;
	char		ind;
	int			i;
	int			pos;

	ind = code[0];
	pos = g_op_tab[ind].code_args ? 2 : 1;
	i = 0;
	ft_printf_fd("%s ", fd, g_op_tab[ind].name);
	while (i < g_op_tab[ind].num_args)
	{
		type = get_arg_type_dasm(ind, code, i);
		write_type_to_fd(type, code, pos, fd);
		pos += get_num_byte(type, g_op_tab[ind].tdir_size);
		++i;
		if (i == g_op_tab[ind].num_args)
			ft_printf_fd("\n", fd);
		else
			ft_printf_fd(", ", fd);
	}
	return (pos);
}

void			write_code_to_fd(char *code, int size, int fd)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (code[i] == 0 || code[i] > 16 || i == size - 1 || i + instruct_len(&(code[i])) > size)
			++i;
		else
			i += write_instruction_to_fd(&(code[i]), fd);
	}
}

void			write_name_comment_to_fd(char *name, char *comment, int fd)
{
	ft_printf_fd(".name \"%s\"\n", fd, name);
	ft_printf_fd(".comment \"%s\"\n\n", fd, comment);
}
