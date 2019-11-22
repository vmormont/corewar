/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 14:24:03 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_champ_num(char *num)
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




static void set_champ_code(t_vm *vm)
{
	t_champ		*player;
	int			offset_start_code;
	int			i;
	t_cursor	*cursor;

	offset_start_code = MEM_SIZE / 3;
	player = vm->champs;
	i = 0;
	while(player)
	{
		ft_memcpy((void*)vm->arena + i, (void*)player->code, player->code_size);
		cursor	= new_cursor(i);
		i += offset_start_code;
		player = player->next;
	}
}

static int	count_champs(t_champ *champ)
{
	int		i;

	i = 0;
	while (champ)
	{
		i++;
		champ = champ->next;
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int i;
	
	t_vm	*vm;
	char	arena[MEM_SIZE];
	t_champ	*champ;

	argc == 1 ? ft_exit(USAGE, NULL) : 0;
	validity_core_args(argv + 1);
	vm = (t_vm*)malloc(sizeof(t_vm));
	argv++;
	while (*argv)
	{
		champ = get_champion_from_file(*argv);
		add_champion2end(&vm->champs, champ);
		argv++;
	}
	set_champ_code(vm);
	dump_arena(vm->arena);
	return (0);
}

