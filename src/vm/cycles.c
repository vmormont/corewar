/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/18 16:10:10 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

t_function	g_operation[] = {NULL, &op_live, &op_ld, &op_st, &op_add,\
	&op_sub, &op_and, &op_or, &op_xor, &op_zjmp, &op_ldi, &op_sti,\
	&op_fork, &op_lld, &op_lldi, &op_lfork, &op_aff};

static void 	zero_champs_live_in_period(t_champ *champs)
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
		cursor->cycles2go = 0;
	}
	else
		cursor->cycles2go = g_op_tab[cursor->op_code].cycles2go;
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
			if (vm->options.verbos == V_DEATHS)
			{
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",\
				temp->id, vm->cycles - temp->cycle_live, vm->cycles_to_die);
			}
			kill_cursor(&vm->cursors, temp, vm->visual);
			vm->num_of_cursors -= 1;
		}
		else
			first = first->next;
	}

	// если количество операций live в cycle2die циклов больше NBR_LIVE
	// или число проверок без уменьшения превысило MAX_CHECKS
	if (vm->num_live_op >= NBR_LIVE || vm->checks_without_dec_cycle2die == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		if (vm->options.verbos == V_CYCLE)
			ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);
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

static void		log_moves(t_vm *vm, t_cursor *cursor)
{
	int			i;

	if (cursor->step > 1)
	{
		ft_printf("ADV %d (%06p -> %06p) ", cursor->step,\
		(uintptr_t)(cursor->pos),\
		(uintptr_t)((cursor->pos + cursor->step)));
		i = cursor->pos;
		while (i < (cursor->pos + cursor->step))
		{
			ft_printf("%x%x ",\
			(vm->arena[i % MEM_SIZE] & 0xF0) >> 4,\
			vm->arena[i % MEM_SIZE] & 0xF);
			++i;
		}
		ft_printf("\n");
	}
}

void			cycle(t_vm *vm)
{
	t_cursor	*temp;

	//пока живы процессы, игра продолжается
	while (vm->cursors)
	{
		// если стоит флаг dump завешаем цикл
		if (vm->cycles == vm->options.dump)
			break ;
		// увеличиваем счетчик цикла и цикла с последней проверки
		vm->cycles += 1;
		vm->cycles_from_last_check += 1;
		if (vm->options.verbos == V_CYCLE)
			ft_printf("It is now cycle %d\n", vm->cycles);

		temp = vm->cursors;
		//проходим по каждому процессу
		while (temp)
		{
			if (!temp->cycles2go)
				// считываем следующий код операции и выставляем cycles2go
				// согласно коду операции
				initial_read_cursor(temp, vm->arena);
			//уменьшаем количество циклов до исполнения
			if (temp->cycles2go > 0)
				temp->cycles2go -= 1;

			if (!temp->cycles2go)
			{
				//проводим валидацию кодов аргументов
				//если успешно, выполняем операцию
				if (check_op_code_and_type_args(temp, vm->arena))
					g_operation[temp->op_code](vm, temp);

				if (vm->options.verbos == V_MOVE)
					log_moves(vm, temp);
				//в массиве положений кареток убираем одну каретку по старой позиции
				vm->visual ? vm->visual->cursors_pos[temp->pos]-- : 0;
				//сдвигаем позицию каретки на длину операции
				temp->pos = (temp->pos + temp->step) % MEM_SIZE;
				//добавляем одну каретку в новую позицию
				vm->visual ? vm->visual->cursors_pos[temp->pos]++ : 0;
			}
			//уменьшаем количество циклов до исполнения
			temp = temp->next;
		}
		// если количество циклов с последней проверки
		// сравнялось с cycle_to_die проводим проверку кареток
		if(vm->cycles_from_last_check >= vm->cycles_to_die)
			check_cursors(vm);
	}
}
