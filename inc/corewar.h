/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/26 13:36:38 by astripeb         ###   ########.fr       */
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

typedef enum	e_error
{
	NONE,
	USAGE = 300,
	FILE_EXTENSION_ERROR,
	ARG_OPTION_ERROR,
	CHAMP_NUM_ERROR,
	HEAD_SIZE_ERROR,
	EXEC_CODE_ERROR,
	EXEC_SIZE_ERROR,
	NO_CODE_ERROR,
	CODE_SIZE_ERROR,
	MANY_CHAMPS_ERROR
}				t_error;

/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, char *file_name, t_vm **vm);

void			ft_exit_read(t_error err, char *file,\
				t_champ **champs, int exec_size);

/*
** OPTIONS
*/

t_options		get_options(int ac, char **av);

void			print_options(t_options options);

/*
** CHAMPION FUNCTIONS
*/

t_champ			*create_new_champ(t_header *head, void *code);

void			del_one_champion(t_champ **begin);

void			del_champions(t_champ **champ);

void			add_champion2end(t_champ **begin, t_champ *champ, int index);

void			read_champions_from_args(int ac, char **av, t_champ **champs);

void			sort_and_check_champs(t_champ *champs);

void			print_champs(t_champ *champ);

/*
** UTILLITY VM
*/

t_vm			*create_vm(t_champ *champs, t_options options);

void 			set_champ_code_on_arena(t_vm *vm);

void			destroy_vm(t_vm **vm);

/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

void			dump_arena(char *arena);

int				isdigit_word(char *word);

int				is_filename_extension(char *filename, char *extension);

void			ft_swap(void **a, void **b);

/*
** CURSOR
*/

t_cursor		*new_cursor(int pos);

t_cursor		*copy_cursor(t_cursor *src, int pos, char mode);

void			add_cursor(t_cursor **list, t_cursor *cursor);

void			kill_cursor(t_cursor **list, t_cursor *cursor);

void			kill_all_cursors(t_cursor **begin);

/*
** CYCLES FUNCTION
*/

void			cycle(t_vm *vm);

/*
** READ & WRITE FUNCTIONS
*/

int				read_4_bytes(char *arena, int index);

short			read_2_bytes(char *arena, int index);

void			copy_4_bytes(char *arena, int index, int num);

void			copy_2_bytes(char *arena, int index, short num);

#endif
