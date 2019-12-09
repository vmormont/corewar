/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/09 17:59:25 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

extern t_function g_operation[];

static void zero_champs_live_in_period(t_champ *champs)
{
	while (champs)
	{
		champs->lives_in_period = 0;
		champs = champs->next;
	}
}

static void		initial_read_cursor(t_cursor *cursor, char *arena)
{
	cursor->op_code = arena[cursor->pos % MEM_SIZE];
	if (cursor->op_code < 1 || cursor->op_code > 17)
	{
		cursor->step = 1;
		cursor->cycles2go = 1;
	}
	else
		cursor->cycles2go = g_op_tab[cursor->op_code].cycles2go - 1;
	cursor->exec = TRUE;
}

static void		check_cursors(t_vm *vm)
{
	t_cursor	*first;
	t_cursor	*temp;

	// обнуляем переменную
	vm->cycles_from_last_check = 0;

	first = vm->cursors;
	// идем по процессам
	while (first)
	{
		// если процесс не отзывался последний раз в прошлом
		// cycle2die периоде убиваем его
		if (((vm->cycles - first->cycle_live) >= vm->cycles_to_die) || vm->cycles_to_die <= 0)
		{
			temp = first;
			first = first->next;
			kill_cursor(&vm->cursors, temp);
		}
		else
			first = first->next;
	}

	// если количество операций live в cycle2die циклов больше NBR_LIVE
	// или число проверок без уменьшения превысило MAX_CHECKS

	if (vm->num_live_op >= NBR_LIVE || vm->checks_without_dec_cycle2die == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks_without_dec_cycle2die = 1;
	}
	// увеличиваем число циклов без уменьшения cycle2die
	else
		vm->checks_without_dec_cycle2die += 1;
	//обнуляем общее количество операций live в цикле
	vm->num_live_op = 0;
	//обнуляем live_in_period у чемпионов
	zero_champs_live_in_period(vm->champs);
}

static t_bool	validation_arg(char op_code, t_arg_type type, char num_arg)
{
	char	code_arg;

	code_arg = g_op_tab[op_code].args[num_arg];
	if (type == REG_CODE && !((( code_arg >> 4) & REG_CODE) ^ REG_CODE))
		return (TRUE);
	else if (type == DIR_CODE && !(((code_arg >> 2) & DIR_CODE) ^ DIR_CODE))
		return (TRUE);
	else if (type == IND_CODE && !((code_arg & IND_CODE) ^ IND_CODE))
		return (TRUE);
	return (FALSE);
}

static char		check_op_code_and_type_args(t_cursor *cursor, char *arena)
{
	t_arg_type	type;
	char		code;
	char		i;
	char		exec;

	i = 0;
	exec = 1;
	if (cursor->op_code < 1 || cursor->op_code > 16)
		return (0);
	if (g_op_tab[cursor->op_code].code_args)
	{
		cursor->step = OP_SIZE + ARGS_SIZE;
		code = arena[(cursor->pos + OP_SIZE) % MEM_SIZE];
		while (i < g_op_tab[cursor->op_code].num_args)
		{
			type = (code >> (6 - (2 * i)) & 3);
			if(type == REG_CODE)
				cursor->step += 1;
			else if (type == DIR_CODE)
				cursor->step += (4 - (2 * g_op_tab[cursor->op_code].tdir_size));
			else if (type == IND_CODE)
				cursor->step += IND_SIZE;
			exec = validation_arg(cursor->op_code, type, i) ? exec : 0;
			i++;
		}
	}
	else
		cursor->step = OP_SIZE + (4 - (2 * g_op_tab[cursor->op_code].tdir_size));
//ft_printf("op code = %d, code args = %d, 1 = [%d], 2 = [%d], 3 = [%d], step = %d\n", cursor->op_code,
//	g_op_tab[cursor->op_code].code_args, (code >> 6) & 3, (code >> 4) & 3, (code >> 2) & 3, cursor->step);
	return (exec);
}

void	cycle(t_vm *vm)
{
	t_cursor	*temp;

	//пока живы процессы, игра продолжается (?): да (!)
	while (vm->cursors)
	{
		// увеличиваем счетчик цикла и цикла с последней проверки
		//ft_printf("It is now cycle %d\n", vm->cycles);

		//if (vm->cycles == 4159)
		//	temp += 0;
		vm->cycles += 1;
		vm->cycles_from_last_check += 1;
		temp = vm->cursors;
		//проходим по каждому процессу
		while (temp)
		{

			temp->cycles2go -= 1;
			//если пришло время исполниться
			temp->cycles2go == -1 ? initial_read_cursor(temp, vm->arena) : 0;
			if (!temp->cycles2go)
			{
				//проводим валидацию кодов аргументов
				//если успешно, выполняем операцию
				if (check_op_code_and_type_args(temp, vm->arena))
					g_operation[temp->op_code](vm, temp);

				//сдвигаем позицию каретки на длину операции
				temp->pos = (temp->pos + temp->step) % MEM_SIZE;

				// считываем следующий код операции и выставляем cycles2go
				// согласно коду операции

			}
			//уменьшаем количество циклов до исполнения
			temp = temp->next;
		}
		// если количество циклов с последней проверки
		// сравнялось с cycle_to_die проводим проверку кареток
		if(vm->cycles_from_last_check >= vm->cycles_to_die)
			check_cursors(vm);

		// если стоит флаг dump завешаем цикл
		if (vm->cycles == vm->options.dump)
		{
			dump_arena(vm->arena);
			break ;
		}
	}
}
