 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:46:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/16 16:31:16 by pcredibl         ###   ########.fr       */
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
** ./corewar [-d N -s N -v N | -b --stealth | -t --stealth] [-a] <champion1.cor>
** ############################################################################
** -n [1..4] <champion1.cor>	- Number of champion
** ############################################################################
** -a			- Prints output from "aff" (Default is to hide it)
** ############################################################################
** -d [1..INT_MAX]	- Dumps memory after N cycles then exits
** -s [1..INT_MAX]	- Runs N cycles, dumps memory, pauses, then repeats
** -v N			- Verbosity levels, can be added together to enable several
**  				- 0 : Show only essentials
**  				- 1 : Show lives
**  				- 2 : Show cycles
**  				- 4 : Show operations
**  				- 8 : Show deaths
**  				- 16 : Show PC movements (Except for jumps)
** ############################################################################
** -t			- Terminal output mode
** 	--stealth	- Hides the real contents of the memory
** ############################################################################
*/

typedef struct				s_options
{
	char					aff;
	int						dump;
	int						cycles;
	char					verbos;
	char					terminal;
}							t_options;

/*
** КАРЕТКА
** id						- уникальный номер каретки
** reg[MAX_REG]				- регистры каретки
** carry					- флаг carry
** pos						- позиция каретки
** op_code					- код операции на котором стоит каретка
** cycles_to_exec			- время до выполнения операции, на котором стоит каретка
** step						- кол-во байт, которое должна перешагнуть каретка,
**							  чтоб оказаться на следующей команде
** cycle_live				- цикл, в который данной кареткой в последний\
**							  раз выполнялась команда live
*/

typedef struct				s_cursor
{
	int						id;
	int						reg[REG_NUMBER + 1];
	t_bool					carry;
	unsigned int			pos;
	char					op_code;
	int						cycles2go;
	int						step;
	int						cycle_live;
	t_bool					exec;
	struct s_cursor			*next;
}							t_cursor;

/*
** ВИРТУАЛЬНАЯ МАШИНА
** champs					- список игроков
** cursors					- список кареток
** options					- опиции, считанные из командной строки
** cycles					- количество пройденных циклов
** cycles_to_die			- количество оставшихся до конца партии циклов
** num_of_champs			- количество игроков
** num_of_cursors			- количество курсоров
** arena[MEM_SIZE]			- арена
** num_live_op				- количество операций live в данном цикле
** checks_without_dec_cycle2die
** 							- количество проверок без уменьшения парметра cycle_to_die
**	winner					- id последнего сказавшего live чемпиона
*/

typedef struct				s_vm
{
	struct s_champ			*champs;
	struct s_cursor			*cursors;
	t_options				options;
	int						cycles;
	int						cycles_to_die;
	char					num_of_champs;
	unsigned long long int	num_of_cursors;
	char					arena[MEM_SIZE];
	int						num_live_op;
	int						checks_without_dec_cycle2die;
	int						cycles_from_last_check;
	char					winner;
}							t_vm;

/*
** ЧЕМПИОН
** считанный из *.cor файла
** id						- порядковый номер игрока
** magic					- magic_header_code
** name						- имя игрока
** comment					- комментарий
** code						- код, считанный из файла
** code_size				- размер исполняемого кода
** last_live				- последний cycle когда, команда live указала на игрока
** lives_in_period			- кличество операций live совершенное чемпионом в текущем цикле (нужно для визуализации)
** next						- указатель на следующего чемпиона
*/

typedef	struct				s_champ
{
	int						id;
	int						magic;
	char					*name;
	char					*comment;
	void					*code;
	int						code_size;
	int						last_live;
	int						lives_in_period;
	struct s_champ			*next;
}							t_champ;

#endif
