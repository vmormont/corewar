/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:49:45 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/15 19:48:56 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define INVALID_FILE_NAME 200
# define USAGE 201
# define NAME_ERROR 202
# define COMMENT_ERROR 203
# define LEXICAL_ERROR 204

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

/*
** MANAGMENT ERRORS
*/

void		ft_exit(t_champ **champ, int err);

void		lexical_error(t_champ **champ, char *data, char *err_adr);

/*
** UTILITY FUNCTIONS
*/

int			skip_spaces(char *filedata, int index);

int			skip_spaces_2next_line(char *filedata, int index);

char		*get_clean_data_from_file(t_champ *champ, char *filename);

/*
** CHAMPION FUNCTIONS
*/

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

void		create_cor_file(char *src_file);

/*
** LEXICAL FUNCTIONS
*/

void		lexical_analizer(t_champ *champ, char *datafile);

int			parse_name(t_champ *champ, char *data);

int			ft_islabel(char c, char *label_chars);

int			parse_label(t_champ *champ, char *filedata, int i);

int			parse_instruction(t_champ *champ, char *filedata, int index);

int			parse_arguments(t_champ *champ, t_instr *instruction,
			char *filedata, int index);

/*
** INSTRUCTIONS FUNCTIONS
*/

t_instr		*new_instruct(t_op *op);

t_instr		*add_instr2end(t_instr *start, t_instr *instr);

void		del_one_instr(t_instr **instr);

void		del_instr(t_instr **begin);

t_op		*create_op_tab(void);

int			get_op_code(t_op *op_tab, char *name);

void		print_op_tab(t_op *op_tab);

void		print_instruct(t_instr *instr);

int			define_instruct_size(t_instr *instr);

int			define_instruct_offset(t_instr *begin);

/*
** ARGGUMENTS FUNCTIONS
*/

int			possible_arg(char arg, char mask);

void		print_args(t_arg *args, int num);

/*
** LABEL FUNCTIONS
*/

t_label		*add_label2end(t_label *begin, char *title, size_t offset);

void		del_label(t_label **begin);

void		print_label(t_label *label);

/*
** VALIDATION FUNCTION
*/

int			valid_label(char *arg, t_label *label);

int			valid_direct(char *arg, t_label *label);

int			valid_indirect(char *arg, t_label *label);

int			valid_register(char *arg);

#endif
