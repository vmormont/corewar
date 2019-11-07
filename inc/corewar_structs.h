/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:29:02 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/07 21:29:02 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCTS_H
# define COREWAR_STRUCTS_H

/*
** THIS HEADER ONLY FOR STRUCTURES
** AND DEFINE COSTANTS NEEDED FOR PROJECT COREWAR
*/

# include "op.h"
# include "libftprintf.h"

/*
** КОДЫ ТИПОВ АРГУМЕНТОВ
** нужны определения необходимости добавления
** байта "Кода типов аргументов""
** bin - 0111 1111 0110 1101
** hex – 0xb6fe
** dec - 48846
*/

#define CODE_TYPES	0xb6fe

/*
** Максимальное количество аргументов в инструкции
*/

#define MAX_ARGS	3

/*
** АРГУМЕНТ
** type 	- тип (T_REG | T_DIR | T_IND)
** str		- содержимое ("r1", "loop", "%3", "3")
** value	- значение содержимого
*/

typedef struct	s_arg
{
	char			type;
	char			*str;
	int				value;
}				t_arg;

/*
** ИНСТРУКЦИЯ (двусвязный(?) список)
** label 	- метка интрукции (опционально)
** code 	- код инструкции (live, ld, and e.t.)
** size 	- размер инструкции в байтах
** args_c	- код типов аргументов
** argc[3]	- аргументы инструкции
** next		- следующая инструкция
** prev		- предыдущая инструкция
*/

typedef struct	s_instr
{
	char			*label;
	int				code;
	size_t			size;
	char			code_args;
	t_arg			args[MAX_ARGS];
	struct s_instr	*next;
	struct s_instr	*prev;
}				t_instr;

/*
** ЧЕМПИОН
** name 	- имя
** comment	- комментарий к имени
** instr	- список на набор инструкций-действий
*/

typedef struct	s_champ
{
	char			*name;
	char			*comment;
	struct s_instr	*instr;
}				t_champ;

#endif
