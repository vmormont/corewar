/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:31:06 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/09 14:22:05 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define INVALID_FILE_NAME 200
# define USAGE 201

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>

# include "corewar_structs.h"

t_op		*create_op_tab(void);

void		print_op_tab(t_op *op_tab);

int			get_op_code(t_op *op_tab, char *name);

int			possible_arg(char arg, char mask);

t_champ		*create_champ(void);

void		free_champ(t_champ **champ);

void			ft_exit(int err);

#endif
