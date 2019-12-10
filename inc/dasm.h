/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmormont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:37:08 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/10 23:16:08 by vmormont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

#include "corewar.h"
#include "op.h"
#include "op_struct.h"

/*
** WRITE TO FD FUNCTIONS
*/

int				ft_printf_fd(const char *frm, int fd, ...);
void			write_name_comment_to_fd(char *name, char *comment, int fd);
void			write_code_to_fd(char *code, int size, int fd);
int				write_instruction_to_fd(char *code, int fd);
void			write_type_to_fd(char type, char *code, int pos, int fd);

/*
** UTILLITY DASM
*/

int				create_s_file(char *name);
int				instruct_len(char *instuct);
int				get_num_byte(char type, char t_dir_size);
char			get_arg_type_dasm(char ind, char *code, int index);

/*
** DISASSEMBLER
*/

void			disassemble(t_champ *champs, char **argv);

#endif