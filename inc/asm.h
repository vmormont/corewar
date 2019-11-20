/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:49:45 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/20 13:45:10 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

# define USAGE 200
# define INVALID_FILE_NAME 201
# define NAME_LEN_ERROR 202
# define COMMENT_LEN_ERROR 203
# define EXEC_CODE_ERROR 204
# define NO_CODE_ERROR 205

/*
** MANAGMENT ERRORS
*/

void		ft_exit(t_champ **champ, int err);

void		error_manager(t_champ **champ, char *error_address, char token);

void		invalid_parameter(t_champ **champ, char *data,\
			t_instr *instruction, int param);

/*
** UTILITY FUNCTIONS
*/

char		*get_clean_data_from_file(t_champ *champ, char *filename);

void		print_error_position(char *data, char *error_address);

/*
** CHAMPION FUNCTIONS
*/

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

/*
** INSTRUCTIONS FUNCTIONS
*/

t_instr		*new_instruct(t_op *op);

void		add_instr2end(t_instr **begin, t_instr *instr);

void		del_one_instr(t_instr **instr);

void		del_instr(t_instr **begin);

t_instr 	*last_instruction(t_instr *instr);

int			size_instr(t_instr *instr);

/*
** LABEL FUNCTIONS
*/

t_label		*new_label(size_t offset);

void		add_label2end(t_label **begin, t_label *label);

void		del_one_label(t_label **label);

void		del_label(t_label **begin);

/*
** LEXICAL FUNCTIONS
*/

void		asm_file_parser(t_champ *champ, char *datafile);

int			parse_name(t_champ *champ, char *data);

int			parse_label(t_champ *champ, char *filedata, int i);

int			islabel(char *data);

int			parse_arguments(t_champ *champ, t_instr *instruction,
			char *filedata, int index);

int			valid_argument(char *arg, char type, t_label *label);

void		assign_arguments_values(t_champ *champ);

/*
** PARSING UTILITY FUNCTIONS
*/

int			skip_spaces(char *filedata, int index);

int			isseparator(char c);

int			islabelchar(char c, char *label_chars);

int			isinstruct(char *name);

/*
** WRITE CHAMP IN FILE FUNCTION
*/

int			create_cor_file(char *src_file, t_champ *champ);

t_header	*create_header(t_champ *champ);

void		write_champ_in_file(int fd, t_champ *champ);

int			define_code_args(t_instr *instr);

int			reverse_bits(int num, char full_bit);

/*
** PRINT FUNCTIONS
** DELETE BEFORE DEFENCE
*/

void		print_instruct(t_instr *instr);

void		print_args(t_arg *args, int num);

void		print_label(t_label *label);

#endif
