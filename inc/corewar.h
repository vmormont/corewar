/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/21 15:36:37 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"
# include "visual.h"
# include "visual_struct.h"

# define DUMP_COLUMNS	64
# define DUMP_ROWS		64

# define OP_SIZE 1
# define ARGS_SIZE 1
# define PRE_SIZE 2
# define ARENA_REG_SIZE 1

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

enum			e_verbos
{
	V_NONE,
	V_LIVE = 1,
	V_CYCLE = 2,
	V_OPERATIONS = 4,
	V_DEATHS = 8,
	V_MOVE = 16
};

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

void			announce_winner(t_vm *vm);

/*
** UTILLITY VM
*/

t_vm			*create_vm(t_champ *champs, t_options options);

void			set_champ_code_on_arena(t_vm *vm);

void			destroy_vm(t_vm **vm);

void			log_moves(t_vm *vm, t_cursor *cursor);

/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

void			dump_arena(char *arena);

t_bool			isdigit_word(char *word);

t_bool			is_filename_extension(char *filename, char *extension);

void			ft_swap(void **a, void **b);

void			introduce(t_champ *champ);

/*
** CURSOR
*/

t_cursor		*new_cursor(unsigned int pos);

t_cursor		*copy_cursor(t_cursor *src, unsigned int pos);

void			add_cursor(t_cursor **list, t_cursor *cursor);

void			kill_all_cursors(t_cursor **begin);

void			check_cursors(t_vm *vm);

/*
** CYCLES FUNCTION
*/

void			cycle(t_vm *vm);

t_bool			check_op_code_and_type_args(t_cursor *cursor, char *arena);

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

int				get_arg_size(char op_code, t_arg_type type);

int				read_4_bytes(char *arena, unsigned int index);

short			read_2_bytes(char *arena, unsigned int index);

void			copy_4_bytes(char *arena, unsigned int index, int num);

int				get_arg_value(char *arena, t_cursor *cursor, t_arg_type type);


//УДОЛИТЬ!!!
void			print_cursor_map(int *map);

void			print_reg(int *reg);

void			print_options(t_options options);

#endif
