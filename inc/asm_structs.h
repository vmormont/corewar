/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:00:23 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 16:22:22 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCTS_H
# define ASM_STRUCTS_H

/*
** THIS HEADER ONLY FOR ASM STRUCTURES
*/

# include "op.h"
# include "libftprintf.h"

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
	t_arg_type		type;
	char			*str;
	int				value;
}				t_arg;

/*
** ИНСТРУКЦИЯ (двусвязный(?) список)
** code 		- код инструкции (live -> 1, ld -> 2, lfork ->15 and e.t.)
** offset 		- смещение инструкции относительно начала КОДА чемиона
** code_args	- код типов аргументов
** args[3]		- аргументы инструкции
** num_args		- количество аргументов
** instr_size	- размер в байтах инструкции
** cycles2go	- циклов до исполнения
** tdir_size	- размер T_DIR (0 - 4 байта, 1 - 2 байта)
** next			- следующая инструкция (под вопросом)
** prev			- предыдущая инструкция (под вопросом)
*/

typedef struct	s_instr
{
	int				code;
	size_t			offset;
	char			code_args;
	t_arg			*args;
	int				num_args;
	size_t			instr_size;
	int				cycles2go;
	char			tdir_size;
	struct s_instr	*next;
	struct s_instr	*prev;
}				t_instr;

/*
**	ДОПУСТИМЫЙ ТИП АРГУМЕНТОВ ДЛЯ ИНСТРУКЦИИ
**				   T_REG  T_DIR T_IND
**	DIR			00	 00     10	  00	-> 8
**	REG			00	 01  	00	  00	-> 16
**	DIR/IND		00	 00  	10	  11	-> 11
**	REG/DIR		00	 01  	10	  00	-> 24
**	REG/IND		00	 01  	00	  11	-> 19
**	REG/DIR/IND	00	 01		10	  11	-> 27
**
** СТРУКТУРА ИНСТРУКЦИИ
** name			- имя инструкции
** num_args		- количество небходимых аргументов
** args[1-3]	- аргументы
** code			- код инструкции
** cycles2go	- циклов до исполнения
** comment		- комментарий
** code_args	- код типов аргументов (1 - есть, 0 - нет)
** tdir_size	- размер аргумента T_DIR
*/

# define NUMBER_OF_INSTR	16
# define D					8
# define R					16
# define DI					11
# define RD					24
# define RI					19
# define RDI				27

typedef struct	s_op
{
	char			name[6];
	int				num_args;
	char			args[3];
	int				code;
	int				cycles2go;
	char			code_args;
	char			tdir_size;
}				t_op;

/*
** ЧЕМПИОН
** data			- cчитанные в переменную данные из файла
** name 		- имя
** comment		- комментарий к имени
** instr		- список на набор инструкций-действий
** labels		- список меток
*/

typedef struct	s_champ
{
	char			*data;
	char			*name;
	char			*comment;
	struct s_instr	*instr;
	struct s_label	*labels;
}				t_champ;

#endif