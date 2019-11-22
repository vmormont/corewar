/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_corewar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:58:00 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 21:01:20 by astripeb         ###   ########.fr       */
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

void		ft_exit(int err, char *file_name)
{
	if (err == USAGE)
		ft_usage();
	else if (err == FILE_FAILED)
		ft_fprintf(STDERR_FILENO, "Can't read source file %s\n", file_name);
	else if (err == INVALID_CHAMP_NUM)
		ft_fprintf(STDERR_FILENO,\
		"Wrong champ number (1 - %d)\n", MAX_PLAYERS);
	else if (err == WAITING_FILE)
		ft_fprintf(STDERR_FILENO,\
		"Error: corewar waiting for file with champ\n");
	else if (err == FILETYPE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: invalid type of file with champ\n");
	exit(err);
}

void		ft_exit_read(t_error err, char *file, int fd, int exec_size)
{
	if (err == MALLOC_FAILURE)
		ft_fprintf(STDERR_FILENO, "Error: Failed to alloc memory\n");
	else if (err == INVALID_HEAD_SIZE)
		ft_fprintf(STDERR_FILENO, "Error: File %s has a code size that %s\n",\
		file, "differ from what its header says");
	else if (err == EXEC_CODE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s has an invalid header", file);
	else if (err == EXEC_SIZE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s has too large a code (%d bytes > %d%s",\
		file, exec_size, CHAMP_MAX_SIZE, " bytes)\n");
	else if (err == CODE_SIZE_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: File %s size of code is incorrect\n",\
		file);
	else
		perror("Error");
	close(fd);
	exit(err);
}
