/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:37:50 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 16:03:42 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	valid_label(char *arg)
{
	int i;

	i = 0;
	if (arg[i++] == LABEL_CHAR)
	{
		while (islabelchar(arg[i], LABEL_CHARS))
			++i;
		i = skip_spaces(arg, i);
	}
	return (i);
}

static int	valid_direct(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == DIRECT_CHAR)
	{
		if (arg[++i] == LABEL_CHAR)
		{
			if (!(i += valid_label(&arg[i])))
				return (0);
		}
		else
		{
			if (ft_isdigit(arg[i]) || arg[i] == '-')
			{
				i += arg[i] == '-' ? 1 : 0;
				while (ft_isdigit(arg[i]))
					++i;
				i = skip_spaces(arg, i);
			}
			else
				i = 0;
		}
	}
	return (i);
}

static int	valid_indirect(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == LABEL_CHAR)
	{
		if (!(i = valid_label(&arg[i])))
			return (0);
	}
	else
	{
		i += arg[i] == '-' ? 1 : 0;
		while (ft_isdigit(arg[i]))
			++i;
		i = skip_spaces(arg, i);
	}
	return (i);
}

static int	valid_register(char *arg)
{
	int i;
	int	reg_num;

	i = 0;
	if (arg[i++] != REG_CHAR)
		return (0);
	reg_num = ft_atoi(&arg[i]);
	if (reg_num < 1 || reg_num > REG_NUMBER)
		return (0);
	while (ft_isdigit(arg[i]))
		++i;
	i = skip_spaces(arg, i);
	return (i);
}

int			valid_argument(char *arg, t_arg_type type)
{
	int		valid;

	valid = 0;
	if (type == T_DIR)
		valid = valid_direct(arg);
	else if (type == T_IND)
		valid = valid_indirect(arg);
	else if (type == T_REG)
		valid = valid_register(arg);
	return (valid);
}
