/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 18:02:16 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

#define DUMP_COLUMNS	64
#define DUMP_ROWS		64

enum			e_error
{
	USAGE = 300,
	FILE_FAILED,
	INVALID_CHAMP_NUM,
	WAITING_FILE,
	TYPE_ERROR,
	NO_CODE_ERROR,
	INVALID_OPTION,
	INVALID_HEAD_SIZE,
	EXEC_CODE_ERROR,
	EXEC_SIZE_ERROR,
	CODE_SIZE_ERROR
}				t_error;

/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, char *file_name, t_vm **vm);

/*
** UTILLITY VM
*/

t_vm			*create_vm(void);

void 			set_champ_code(t_vm *vm);

void			destroy_vm(t_vm **vm);

/*
** OPTIONS
*/

void			check_champ_num(char *num);

void			validity_core_args(char **av);

int				count_champs(t_champ *champ);

/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

void			dump_arena(char *arena);

/*
** CURSOR
*/

t_cursor		*new_cursor(int pos);

t_cursor		*copy_cursor(t_cursor *src, int pos, char mode);

void			add_cursor(t_cursor **list, t_cursor *cursor);

void			kill_cursor(t_cursor **list, t_cursor *cursor);

void			kill_all_cursors(t_cursor **begin);

/*
** CHAMPION FUNCTIONS
*/

t_champ			*get_champion_from_file(char *filename);

void			del_one_champion(t_champ **begin);

void			del_champions(t_champ **champ);

void			add_champion2end(t_champ **begin, t_champ *champ);

#endif
