/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:05:39 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 17:39:11 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_flags(char *flags, long int options)
{
	while (*flags && options)
	{
		if (*flags > 96 && *flags < 123)
		{
			if ((options >> (*flags - 71)) & 1)
				options ^= (1L << (*flags - 71));
		}
		else if (*flags > 64 && *flags < 91)
		{
			if ((options >> (*flags - 65)) & 1)
				options ^= (1L << (*flags - 65));
		}
		flags++;
	}
	return (options ? 0 : 1);
}

static int		check_option(char *str, long int *options)
{
	int i;

	if (str[0] == '-')
	{
		i = 1;
		if (str[i] == 'h')
			return (1);
		while (str[i])
		{
			if (str[i] > 96 && str[i] < 123)
				*options |= (1L << (str[i] - 71));
			else if (str[i] > 64 && str[i] < 91)
				*options |= (1L << (str[i] - 65));
			else
				return (-1);
			++i;
		}
	}
	return (0);
}

int				options(int ac, char **av)
{
	int			i;
	int			check;
	long int	options;

	options = 0;
	i = 0;
	while (i < ac)
	{
		check = check_option(av[i], &options);
		if (check == 1)
			ft_exit(NULL, USAGE);
		if (check == -1)
			ft_exit(NULL, INVALID_OPTION);
		++i;
	}
	if (!check_flags("a", options))
		ft_exit(NULL, USAGE);
	return ((options >> ('a' - 71)) & 1);
}
