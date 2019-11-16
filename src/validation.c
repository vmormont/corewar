/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:37:50 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/16 10:13:10 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	valid_label(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == LABEL_CHAR)
	{
		while (arg[++i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
		{
			if (!islabelchar(arg[i], LABEL_CHARS))
				return (0);
		}
	}
	return (i);
}

int	valid_direct(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == DIRECT_CHAR)
	{
		if (arg[++i] == LABEL_CHAR)
		{
			if (!(i += valid_label(&arg[i], label)))
				return (0);
		}
		else
		{
			i += arg[i] == '-' ? 1 : 0;
			while (arg[i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
			{
				if (!ft_isdigit(arg[i]))
					return (0);
				++i;
			}
		}
	}
	return (i);
}

int	valid_indirect(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == LABEL_CHAR)
	{
		if (!(i = valid_label(&arg[i], label)))
			return (0);
	}
	else
	{
		//get_value(arg[i], )
		i += arg[i] == '-' ? 1 : 0;
		while (arg[i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			++i;
		}
	}
	return (i);
}

int	valid_register(char *arg)
{
	int i;
	int	reg_num;

	i = 0;
	if (arg[i++] != REG_CHAR)
		return (0);
	reg_num = ft_atoi(&arg[i]);
	if (reg_num < MIN_REG && reg_num > MAX_REG)
		return (0);
	while (arg[i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		++i;
	}
	return (i);
}
