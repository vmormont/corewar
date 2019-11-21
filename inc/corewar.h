/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 21:10:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

enum			e_error
{
	USAGE = 300,
	FILE_FAILED,
	INVALID_CHAMP_NUM,
	WAITING_FILE,
	TYPE_ERROR,
	NO_CODE_ERROR,
	INVALID_OPTION,
	INVALID_HEAD_SIZE,
	EXEC_CODE_ERROR,
	EXEC_SIZE_ERROR,
	CODE_SIZE_ERROR
}				t_error;

int		read_cor_file(char *filename);

/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, char *file_name);


/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

/*
** CURSOR
*/

t_cursor		*new_cursor(int pos);

void			add_cursor(t_cursor **list, t_cursor *cursor);

/*
** CHAMPION FUNCTIONS
*/

t_champ			*get_champion_from_file(char *filename);

void			del_one_champion(t_champ **begin);

void			del_champions(t_champ **champ);

void			add_champion2end(t_champ **begin, t_champ *champ);

#endif
