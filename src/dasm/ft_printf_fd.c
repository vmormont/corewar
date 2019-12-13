/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:39:47 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/14 00:40:08 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int				ft_printf_fd(const char *frm, int fd, ...)
{
	va_list			ap;
	t_modific		*mod;
	int				n;

	mod = NULL;
	mod = new_modific(mod, fd);
	va_start(ap, fd);
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
