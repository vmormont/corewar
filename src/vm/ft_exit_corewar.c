/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_corewar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:58:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/25 13:42:57 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_usage(void)
{
	ft_printf("\n\n");
	ft_printf("./corewar [-dump N -s N -v N | -b --stealth | -t --stealth]%s",\
	" [-a] -n N <champ.cor>\n\n");
	print_filler(83, '#', STDOUT_FILENO);
	ft_printf("\n-n [1..4] <champion1.cor>	- Number of champion\n");
	print_filler(83, '#', STDOUT_FILENO);
	ft_printf("\n	-a	- Prints output from 'aff' (Default is to hide it)\n");
	print_filler(83, '#', STDOUT_FILENO);
	ft_printf("\n	-dump [1..INT_MAX]	- %s",\
	"Dumps memory after N cycles then exits\n");
	ft_printf("\n	-s [1..INT_MAX]	- %s",\
	"Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("	-v N            - %s",\
	"Verbosity levels, can be added together to enable several\n");
	ft_printf("\t\t- 0  : Show only essentials\n");
	ft_printf("\t\t- 1  : Show lives\n");
	ft_printf("\t\t- 2  : Show cycles\n");
	ft_printf("\t\t- 4  : Show operations\n");
	ft_printf("\t\t- 8  : Show deaths\n");
	ft_printf("\t\t- 16 : Show PC movements (Except for jumps)\n");
	print_filler(83, '#', STDOUT_FILENO);
	ft_printf("\n	-t			- Terminal output mode\n");
	ft_printf("	--stealth	- Hides the real contents of the memory\n");
	print_filler(83, '#', STDOUT_FILENO);
	ft_printf("\n\n");
}

void		ft_exit(int err, char *file_name, t_vm **vm)
{
	if (err == USAGE)
		ft_usage();
	else if (err == MALLOC_FAILURE)
		ft_fprintf(STDERR_FILENO, "Error: Failed to alloc memory\n");
	destroy_vm(vm);
	exit(err);
}

void		ft_exit_read(t_error err, char *file,\
			t_champ **champs, int exec_size)
{
	if (err == USAGE)
		ft_usage();
	else if (err == HEAD_SIZE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s has a code size that %s\n",\
		file, "differ from what its header says");
	else if (err == ARG_OPTION_ERROR)
		ft_fprintf(STDERR_FILENO,\
		"Error: corewar waiting for file with champ\n");
	else if (err == EXEC_CODE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s has an invalid header", file);
	else if (err == EXEC_SIZE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s has too large a code (%d bytes > %d%s",\
		file, exec_size, CHAMP_MAX_SIZE, " bytes)\n");
	else if (err == CODE_SIZE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s size of code is incorrect\n",\
		file);
	else if (err == CHAMP_NUM_ERROR)
		ft_fprintf(STDERR_FILENO, "Wrong champ number (1 - %d)\n", MAX_PLAYERS);
	else if (err == FILE_EXTENSION_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: Invalid file extension. Need <file_name>.cor\n");
	else
		perror("Error");
	del_champions(champs);
	exit(err);
}
