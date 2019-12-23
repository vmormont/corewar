/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 22:57:15 by astripeb         ###   ########.fr       */
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

static void 	check_cycle2die(t_vm *vm)
{
	t_champ *temp;

	if (vm->num_live_op >= NBR_LIVE || vm->checks_without_dec_cycle2die == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		if (vm->options.verbos == V_CYCLE)
			ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);
		vm->checks_without_dec_cycle2die = 1;
	}
	else
		vm->checks_without_dec_cycle2die += 1;
	vm->num_live_op = 0;
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
	while (temp)
	{
		if (!temp->cycles2go)
			initial_read_cursor(temp, vm->arena);
		if (temp->cycles2go > 0)
			temp->cycles2go -= 1;
		if (!temp->cycles2go)
		{
			if (check_op_code_and_type_args(temp, vm->arena))
				g_operation[temp->op_code](vm, temp);
			if (vm->options.verbos == V_MOVE)
				log_moves(vm, temp);
			if (vm->visual)
				move_cursor(vm, temp);
			temp->pos = (temp->pos + temp->step) % MEM_SIZE;
		}
		temp = temp->next;
	}
}

void			cycle(t_vm *vm)
{
	while (vm->cursors)
	{
		if (vm->cycles == vm->options.dump)
			break ;
		vm->cycles += 1;
		vm->cycles_from_last_check += 1;
		if (vm->options.verbos == V_CYCLE)
			ft_printf("It is now cycle %d\n", vm->cycles);
		check_cycle2go(vm);
		if (vm->cycles_from_last_check >= vm->cycles_to_die)
		{
			check_cursors(vm);
			check_cycle2die(vm);
		}
		if (vm->visual)
			vis_cycle(vm);
	}
}
