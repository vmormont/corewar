/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:38:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 20:36:50 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_option(char ac, char **av, char *option)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!ft_strcmp(&av[i][1], option))
				return (i);
			++i;
		}
		else if (isdigit_word(av[i]) || ft_strstr(av[i], ".cor"))
			++i;
		else
			break ;
	}
	return (0);
}

int			get_option_value(char **av, int index, int min_val, int max_val)
{
	int value;

	value = 0;
	if (isdigit_word(av[index]))
		value = ft_atoi(av[index]);
	else
		ft_exit(USAGE, NULL);
	if (value < min_val || value > max_val)
		ft_exit(USAGE, NULL);
	return (value);
}

static int	check_valid_options(int ac, char **av, char **options, int opt_num)
{
	int i;
	int j;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (j < opt_num)
			{
				if (!ft_strcmp(&av[i][1], options[j]))
					break ;
				++j;
			}
			if (j == opt_num)
				return (0);
		}
		++i;
	}
	return (1);
}

t_options	get_options(int ac, char **av)
{
	t_options	options;
	static char *opt[] = {"n", "dump", "c", "a", "v", "t", "-stealth"};

	if (ac == 1 || !check_valid_options(ac, av, opt, 6))
		ft_exit(USAGE, NULL);
	ft_bzero((void*)&options, sizeof(t_options));
	options.aff = get_option(ac, av, "a");
	if ((options.dump = get_option(ac, av, "dump")))
		options.dump = get_option_value(av, options.dump + 1, 1, INT32_MAX);
	if ((options.cycles = get_option(ac, av, "c")))
		options.cycles = get_option_value(av, options.cycles + 1, 1, INT32_MAX);
	if ((options.verbos = get_option(ac, av, "v")))
	{
		options.verbos = get_option_value(av, options.verbos + 1, 1, 16);
		if (options.verbos != 1 && (options.verbos & (options.verbos - 1)))
			ft_exit(USAGE, NULL);
	}
	if ((options.terminal = get_option(ac, av, "t")))
	{
		if ((get_option(ac, av, "-stealth") - options.terminal) == 1)
			options.terminal = 2;
		else
			options.terminal = 1;
	}
/*
	ft_printf("aff = %d\n", options.aff);
	ft_printf("dump = %d\n", options.dump);
	ft_printf("cycles = %d\n", options.cycles);
	ft_printf("verbos = %d\n", options.verbos);
	ft_printf("terminal = %d\n", options.terminal);
*/
	return (options);
}
