/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/12 14:27:01 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"
# include <ncurses.h>
# include <unistd.h>

# define DUMP_COLUMNS	64
# define DUMP_ROWS		64

# define OP_SIZE 1
# define ARGS_SIZE 1

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
	MANY_CHAMPS_ERROR,
	NCURSES_INIT_ERROR
}				t_error;

typedef void(*t_function)(t_vm *vm, t_cursor *cursor);

/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, t_vm **vm);

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

t_champ			*get_champ_by_id(t_champ *champs, int id);

void			print_champs(t_champ *champ);

void			announce_winner(t_vm *vm);

/*
** UTILLITY VM
*/

t_vm			*create_vm(t_champ *champs, t_options options);

void			set_champ_code_on_arena(t_vm *vm);

void			destroy_vm(t_vm **vm);

int				read_memory(char *arena, int pos, char size);

/*
**	FUNCTION FOR VIZUALIZATION
*/

void			visualizator(t_vm *vm);

/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

void			dump_arena(char *arena);

t_bool			isdigit_word(char *word);

t_bool			is_filename_extension(char *filename, char *extension);

void			ft_swap(void **a, void **b);

void			introduce(t_champ *champ);

void			print_reg(int *reg);

/*
** CURSOR
*/

t_cursor		*new_cursor(unsigned int pos);

t_cursor		*copy_cursor(t_cursor *src, unsigned int pos);

void			add_cursor(t_cursor **list, t_cursor *cursor);

void			kill_cursor(t_cursor **list, t_cursor *cursor);

void			kill_all_cursors(t_cursor **begin);

/*
** CYCLES FUNCTION
*/

void			cycle(t_vm *vm);

/*
** OPERATIONS FUNCTION
*/

void			op_live(t_vm *vm, t_cursor *cursor);

void			op_ld(t_vm *vm, t_cursor *cursor);

void			op_st(t_vm *vm, t_cursor *cursor);

void			op_add(t_vm *vm, t_cursor *cursor);

void			op_sub(t_vm *vm, t_cursor *cursor);

void			op_and(t_vm *vm, t_cursor *cursor);

void			op_or(t_vm *vm, t_cursor *cursor);

void			op_xor(t_vm *vm, t_cursor *cursor);

void			op_zjmp(t_vm *vm, t_cursor *cursor);

void			op_ldi(t_vm *vm, t_cursor *cursor);

void			op_sti(t_vm *vm, t_cursor *cursor);

void			op_fork(t_vm *vm, t_cursor *cursor);

void			op_lld(t_vm *vm, t_cursor *cursor);

void			op_lldi(t_vm *vm, t_cursor *cursor);

void			op_lfork(t_vm *vm, t_cursor *cursor);

void			op_aff(t_vm *vm, t_cursor *cursor);

void			op_lld(t_vm *vm, t_cursor *cursor);

void			op_ldi(t_vm *vm, t_cursor *cursor);

void			op_lldi(t_vm *vm, t_cursor *cursor);

/*
** OPERATIONS UTILITY
*/

t_bool			isregister(char reg_num);

t_arg_type		get_arg_type(char code_args, char num_arg);


/*
** READ & WRITE FUNCTIONS
*/

int				read_4_bytes(char *arena, unsigned int index);

short			read_2_bytes(char *arena, unsigned int index);

void			copy_4_bytes(char *arena, unsigned int index, int num);

#endif
