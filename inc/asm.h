/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:49:45 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/16 14:12:10 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

# define INVALID_FILE_NAME 200
# define USAGE 201

/*
** MANAGMENT ERRORS
*/

void		ft_exit(t_champ **champ, int err);

void		error_manager(t_champ **champ, char *data,\
			char *error_address, char token);

/*
** UTILITY FUNCTIONS
*/

int			skip_spaces(char *filedata, int index);

char		*get_clean_data_from_file(t_champ *champ, char *filename);

/*
** CHAMPION FUNCTIONS
*/

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

void		create_cor_file(char *src_file);

void		create_op_tab(t_op *op_tab);

/*
** LEXICAL FUNCTIONS
*/

void		lexical_analizer(t_champ *champ, char *datafile);

int			parse_name(t_champ *champ, char *data);

int			islabelchar(char c, char *label_chars);

int			parse_label(t_champ *champ, char *filedata, int i);

int			parse_instruction(t_champ *champ, char *filedata, int index);

int			parse_arguments(t_champ *champ, t_instr *instruction,
			char *filedata, int index);

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
** VALIDATION FUNCTION
*/

int			valid_label(char *arg, t_label *label);

int			valid_direct(char *arg, t_label *label);

int			valid_indirect(char *arg, t_label *label);

int			valid_register(char *arg);

int			isseparator(char c);

/*
** PRINT FUNCTIONS
** DELETE BEFORE DEFENCE
*/
void		print_instruct(t_instr *instr);

void		print_args(t_arg *args, int num);

void		print_label(t_label *label);

#endif
