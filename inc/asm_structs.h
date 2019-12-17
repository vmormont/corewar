/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:00:23 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/17 23:06:27 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCTS_H
# define ASM_STRUCTS_H

/*
** THIS HEADER ONLY FOR ASM STRUCTURES
*/

# include "op.h"
# include "op_struct.h"
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
** ИНСТРУКЦИЯ связный список
** code 		- код инструкции (live -> 1, ld -> 2, lfork ->15 and e.t.)
** offset 		- смещение инструкции относительно начала КОДА чемиона
** code_args	- код типов аргументов
** args[3]		- аргументы инструкции
** num_args		- количество аргументов
** instr_size	- размер в байтах инструкции
** cycles2go	- циклов до исполнения
** tdir_size	- размер T_DIR
** next			- следующая инструкция
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
}				t_instr;

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
