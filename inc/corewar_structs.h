/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:46:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/08 21:25:35 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCTS_H
# define COREWAR_STRUCTS_H

/*
** THIS HEADER ONLY FOR STRUCTURES
** AND DEFINE CONSTANTS NEEDED FOR PROJECT COREWAR
*/

# include "op.h"
# include "libftprintf.h"

/*
** КОДЫ ТИПОВ АРГУМЕНТОВ
** нужны для определения необходимости добавления
** байта "Кода типов аргументов""
** bin - 1011 0110 1111 1110, hex – 0xb6fe, dec - 46846
** пример для live: (CODE_TYPES >> (op.code(1) - 1)) & 1 -> Fasle
** пример для lld:	(CODE_TYPES >> (op.code(13) - 1)) & 1 -> True
*/

# define CODE_TYPES	0xb6fe

/*
** РАЗМЕР T_DIR ДЛЯ ИНСТРУКЦИЙ
** нужны определения необходимости добавления
** байта "Кода типов аргументов""
** bin - 1001 0000 1111 1111, hex – 0x90ff, dec - 37119
** пример для live: (OP_DIR_SIZE >> (op.code(1) - 1)) & 1 -> 4 байта
** пример для zjmp: (OP_DIR_SIZE >> (op.code(9) - 1)) & 1 -> 2 байта
*/

# define OP_DIR_SIZE	0x90ff

/*
** МЕТКА
** name			- имя метки
** offset		- смещение инструкции относительно начала КОДА чемиона
*/

typedef struct	s_label
{
	char			*name;
	size_t			offset;
	struct s_label	*next;
}				t_label;

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
** code 		- код инструкции (live -> 1, ld -> 2, lfork ->15 and e.t.)
** offset 		- смещение инструкции относительно начала КОДА чемиона
** code_args	- код типов аргументов
** argc[3]		- аргументы инструкции
** num_args		- количество аргументов
** cycles2go	- циклов до исполнения
** tdir_size	- размер T_DIR (0 - 4 байта, 1 - 2 байта)
** next			- следующая инструкция (под вопросом)
** prev			- предыдущая инструкция (под вопросом)
*/

typedef struct	s_op
{
	int				code;
	size_t			offset;
	char			code_args;
	t_arg			*args;
	int				num_args;
	int				cycles2go;
	char			tdir_size;
	struct s_op		*next;
	struct s_op		*prev;
}				t_op;

/*
** ЧЕМПИОН
** name 		- имя
** comment		- комментарий к имени
** operations	- список на набор инструкций-действий
** labels		- список меток
*/

typedef struct	s_champ
{
	char			*name;
	char			*comment;
	struct s_op		*operations;
	struct s_label	*labels;
}				t_champ;

#endif
