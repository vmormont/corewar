/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:49:45 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/12 21:25:13 by astripeb         ###   ########.fr       */
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

void		ft_exit(t_champ **champ, int err);

void		lexical_error(t_champ **champ, char *data, char *err_adr);

t_op		*create_op_tab(void);

void		print_op_tab(t_op *op_tab);

int			get_op_code(t_op *op_tab, char *name);

/*
** CHAMP FUNCTIONS
*/

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

void		create_cor_file(char *src_file);

/*
** LEXICAL FUNCTIONS
*/

void		lexical_analizer(t_champ *champ, char *datafile);

/*
** INSTR FUNCTIONS
*/

t_instr		*add_instr2end(t_instr *instr, t_op *op);

void		del_instr(t_instr **begin);

void		print_instruct(t_instr *instr);

/*
** ARGS FUNCTIONS
*/

void		del_args(t_arg **args, int num);

int			possible_arg(char arg, char mask);

/*
** LABEL FUNCTIONS
*/

t_label		*add_label2end(t_label *begin);

void		del_label(t_label **begin);

void		print_label(t_label *label);

#endif
