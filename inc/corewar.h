/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 20:18:29 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"


# define FILE_FAILED 300
# define INVALID_CHAMP_NUM 301
# define WAITING_FILE 303
# define TYPE_ERROR 304
# define USAGE 305


/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, char *file_name);

/*
** CURSOR
*/

t_cursor		*new_cursor(int pos);

void			add_cursor(t_cursor **list, t_cursor *cursor);


#endif
