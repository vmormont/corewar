/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 14:36:08 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	check_champ_num(char *num)
{
	int		i;

	i = -1;
	if (!num)
		ft_exit_core(INVALID_CHAMP_NUM, NULL);
	while (num[++i])
		if (!num || !ft_isdigit(num[i]))
			ft_exit_core(INVALID_CHAMP_NUM, NULL);
	if (ft_atoi(num) > MAX_PLAYERS)
		ft_exit_core(INVALID_CHAMP_NUM, NULL);
}

static void	validity_core_args(char **av)
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
			ft_exit_core(FILE_FAILED, av[i]);
		tmp = av[i] + (ft_strlen(av[i]) - 4);
		if (ft_strcmp(tmp, ".cor"))
			ft_exit_core(TYPE_ERROR, NULL);
		waiting_file = 0;
		i++;
	}
	if (waiting_file)
		ft_exit_core(WAITING_FILE, NULL);
}

int		main(int ac, char **av)
{
	int		i;
	t_vm	*vm;

	validity_core_args(av + 1);
	vm = (t_vm*)malloc(sizeof(t_vm));
	
	i = 0;
	return (0);
}

