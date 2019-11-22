/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 14:06:24 by astripeb         ###   ########.fr       */
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

	offset_start_code = MEM_SIZE / vm->num_of_champs;
	player = vm->champs;
	i = 0;
	while(player)
	{
		ft_strncpy(vm->arena + i, (const char*)player->code, player->code_size);
		cursor	= new_cursor(i);
		i += offset_start_code;
		player = player->next;
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
//	char	arena[MEM_SIZE];

	argc == 1 ? ft_exit(USAGE, NULL) : 0;
	char arena[MEM_SIZE];
	ft_bzero((void*)arena, MEM_SIZE);
	arena[42] = 0xFF;
	arena[0] = 0xF;
	arena[2048 + 31] = 0xFF;
//	dump_arena((char*)arena);

//	validity_core_args(argv + 1);
//	vm = (t_vm*)malloc(sizeof(t_vm));
//	ft_bzero((void*)arena, MEM_SIZE);
//	set_champ_code(vm);
	t_champ *champ = get_champion_from_file(argv[1]);
	return (0);
}

