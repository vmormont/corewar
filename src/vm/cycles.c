/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/20 17:45:28 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

t_function	g_operation[] = {NULL, &op_live, &op_ld, &op_st, &op_add,\
	&op_sub, &op_and, &op_or, &op_xor, &op_zjmp, &op_ldi, &op_sti,\
	&op_fork, &op_lld, &op_lldi, &op_lfork, &op_aff};

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

	vm->cycles_from_last_check = 0;
	first = vm->cursors;
	while (first)
	{
		if (((vm->cycles - first->cycle_live) >= vm->cycles_to_die)\
		|| vm->cycles_to_die <= 0)
		{
			temp = first;
			first = first->next;
			if (vm->options.verbos == V_DEATHS)
			{
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",\
				temp->id, vm->cycles - temp->cycle_live, vm->cycles_to_die);
			}
			if (vm->visual)
				clear_cursor(vm, temp->pos, ft_abs(temp->champ->id));
			kill_cursor(&vm->cursors, temp);
			vm->num_of_cursors -= 1;
		}
		else
			first = first->next;
	}
}

static void 	check_cycle2die(t_vm *vm)
{
	t_champ *temp;

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
	temp = vm->champs;
	while (temp)
	{
		temp->lives_in_period = 0;
		temp = temp->next;
	}
}

static void		check_cycle2go(t_vm *vm)
{
	t_cursor	*temp;

	temp = vm->cursors;
	//проходим по каждому процессу
	while (temp)
	{
		if (!temp->cycles2go)
			// считываем следующий код операции и выставляем cycles2go согласно коду операции
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

			if (vm->visual)
				move_cursor(vm, temp);
			//сдвигаем позицию каретки на длину операции
			temp->pos = (temp->pos + temp->step) % MEM_SIZE;
		}
		//уменьшаем количество циклов до исполнения
		temp = temp->next;
	}
}

void			cycle(t_vm *vm)
{
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

		//проходим по каждому процессу и выполняем его если пришлов время
		check_cycle2go(vm);

		// если количество циклов с последней проверки
		// сравнялось с cycle_to_die проводим проверку кареток
		if (vm->cycles_from_last_check >= vm->cycles_to_die)
		{
			vm->visual ? clear_values(vm) : 0;
			check_cursors(vm);
			check_cycle2die(vm);
		}
		if (vm->visual)
		{
			mvwaddstr(vm->visual->menu, 2, 3, vm->visual->pause ? "** PAUSED **" : "** RUNNING **");
			show_values(vm->visual->menu, vm);
			vis_delay(vm->visual);
			vm->visual->pause ? nodelay(stdscr, FALSE) : nodelay(stdscr, TRUE);
		}
	}
}
