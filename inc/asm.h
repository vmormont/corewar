/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:31:06 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/09 13:02:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

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


#endif
