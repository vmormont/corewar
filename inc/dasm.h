/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:37:08 by vmormont          #+#    #+#             */
/*   Updated: 2019/12/24 11:59:21 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include "op.h"
# include "op_struct.h"
# include "libft.h"
# include "libftprintf.h"
# include <stdbool.h>

/*
** Error managment
*/

# define READ_ERROR "can not read file"
# define ERROR_PROG_SIZE "too big size for a champion"
# define ERROR_COMMENT_SIZE "too long length of a comment"
# define MAGIC_ERROR "no equal magic"

/*
** Decimal representation of the instruction number
*/

# define LIVE 1
# define LD 2
# define ST 3
# define ADD 4
# define SUB 5
# define AND 6
# define OR 7
# define XOR 8
# define ZJMP 9
# define LDI 10
# define STI 11
# define FORK 12
# define LLD 13
# define LLDI 14
# define LFORK 15
# define AFF 16

/*
** Additional constants for operation of the disassembler
*/

# define BYTE_SIZE 8
# define NUM_ARG 3
# define REG_DASM 1
# define IND_DASM 3

# define START 0
# define EXTENSION 4

/*
**	Disassemble
*/

void					disassemble(char **argv, int index);

/*
**	Read functions
*/

void					read_cor_head(int fd, t_header *head);

/*
**	Print functions
*/

void					print_name_comment_to_fd(char *name, char *comment,\
												int fd_out);
void					print_code(int fd, int fd_out);

/*
**	Utilits
*/

void					print_usage(void);
void					ft_exit_dasm(char *identifier, int fd);
bool					is_filename_extension(char *filename, char *extension);
char					*get_s_filename(char *arg);
int						reverse_bits(int num, char full_bit);
char					get_num_type(char num, int num_arg);
int						get_num(int fd, size_t t_size, char type);

#endif
