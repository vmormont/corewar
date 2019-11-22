/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:46:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/22 19:41:30 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCTS_H
# define COREWAR_STRUCTS_H

/*
** THIS HEADER ONLY FOR STRUCTURES
** AND DEFINE CONSTANTS NEEDED FOR PROJECT COREWAR
*/

# include "op.h"
# include "op_struct.h"
# include "libftprintf.h"

/*
** КАРЕТКА
** id				- уникальный номер каретки
** reg[MAX_REG]		- регистры каретки
** carry			- флаг carry
** pos				- позиция каретки
** op_code			- код операции на котором стоит каретка
** cycles_to_exec	- время до выполнения операции, на котором стоит каретка
** step				- кол-во байт, которое должна перешагнуть каретка, чтоб оказаться на следующей команде
** cycle_live		- цикл, в который данной кареткой в последний раз выполнялась команда live
*/

typedef struct		s_cursor
{
	int				id;
	char			reg[(REG_NUMBER + 1) * REG_SIZE];
	char			carry;
	int				pos;
	char			op_code;
	int				time_to_exec;
	char			step;
	struct s_cursor	*next;
	int				cycle_live;
}					t_cursor;

/*
** ВИРТУАЛЬНАЯ МАШИНА
** champs			- список игроков
** cursors			- список кареток
** cycles			- количество пройденных циклов
** cycles_to_die	- количество оставшихся до конца партии циклов
** num_of_champs	- количество игроков
** arena[MEM_SIZE]	- арена
** num_live_op		- количество операций live в данном цикле
*/

typedef struct		s_vm
{
	struct s_champ	*champs;
	struct s_cursor	*cursors;
	int				cycles;
	int				cycles_to_die;
	char			num_of_champs;
	char			arena[MEM_SIZE];
	int				num_live_op;
}					t_vm;


/*
** ЧЕМПИОН
** считанный из *.cor файла
** name			- имя игрока
** comment		- комментарий
** code			- код, считанный из файла
** code_size	- размер исполняемого кода
** next			- указатель на следующего чемпиона
*/

typedef	struct s_champ
{
	int				id;
	char			*name;
	char			*comment;
	int				magic;
	int				code_size;
	void			*code;
	struct s_champ	*next;
}				t_champ;

#endif
