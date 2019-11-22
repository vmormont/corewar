/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:38:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 14:39:28 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

void	check_champ_num(char *num)
{
	int		i;

	i = -1;
	if (!num)
		ft_exit(INVALID_CHAMP_NUM, NULL);
	while (num[++i])
		if (!num || !ft_isdigit(num[i]))
			ft_exit(INVALID_CHAMP_NUM, NULL);
	if (ft_atoi(num) > MAX_PLAYERS)
		ft_exit(INVALID_CHAMP_NUM, NULL);
}

void	validity_core_args(char **av)
{
	int		i;
	int		fd;
	char	waiting_file;
	char	*tmp;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			check_champ_num(av[++i]);
			i++;
			waiting_file = 1;
			continue ;
		}
		if ((fd = open(av[i], O_RDONLY)) < 0)
			ft_exit(FILE_FAILED, av[i]);
		close(fd);
		tmp = av[i] + (ft_strlen(av[i]) - 4);
		if (ft_strcmp(tmp, ".cor"))
			ft_exit(TYPE_ERROR, NULL);
		waiting_file = 0;
		i++;
	}
	if (waiting_file)
		ft_exit(WAITING_FILE, NULL);
}
