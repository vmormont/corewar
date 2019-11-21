/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:49:45 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/21 16:16:58 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "asm_structs.h"
# include "op.h"

# define REG_CHAR 	'r'

enum			e_error
{
	USAGE = 200,
	INVALID_FILE_NAME,
	NAME_LEN_ERROR,
	COMMENT_LEN_ERROR,
	NO_CODE_ERROR,
	INVALID_OPTION
}				t_error;

enum			e_token
{
	T_NONE,
	T_ENDLINE = T_LAB + 1,
	T_NAME,
	T_COMMENT,
	T_SEPARATOR,
	T_INSTRUCTION,
	T_PARAMETER,
	T_LABEL,
	T_DIR_LABEL,
	T_IND_LABEL,
	T_NO_LABEL,
	T_END
}				t_token;

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

void		print_error_position(char *data, char *error_address);

int			reverse_bits(int num, char full_bit);

char		*ft_strlstr(char *src, char *pattern, int len);

int			options(int ac, char **av);

/*
** CHAMPION FUNCTIONS
*/

char		*get_clean_data_from_file(t_champ *champ, char *filename);

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

t_header	*create_head_of_champion(t_champ *champ);

/*
** INSTRUCTIONS FUNCTIONS
*/

t_instr		*new_instruct(t_op *op);

void		add_instr2end(t_instr **begin, t_instr *instr);

void		del_one_instr(t_instr **instr);

void		del_instr(t_instr **begin);

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

int			parse_arguments(t_champ *champ, t_instr *instruction,
			char *filedata, int index);

int			valid_argument(char *arg, t_arg_type type, t_label *label);

void		assign_arguments_values(t_champ *champ);

/*
** PARSING UTILITY FUNCTIONS
*/

int			skip_spaces(char *filedata, int index);

int			isseparator(char c);

int			islabel(char *data);

int			islabelchar(char c, char *label_chars);

int			isinstruct(char *name);

/*
** ASSEMBLY CHAMP CODE IN FILE FUNCTIONS
*/

void		assembly(t_champ *champ, char *s_file);

int			define_code_args(t_instr *instr);

void		dump_to_stdout(t_champ *champ);

/*
** PRINT FUNCTIONS
** DELETE BEFORE DEFENCE
*/

void		print_instruct(t_instr *instr);

void		print_args(t_arg *args, int num);

void		print_label(t_label *label);

#endif
