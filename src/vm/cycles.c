/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/28 16:47:50 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

extern t_function g_operation[];

/*
static void	define_step_and_time_cursor(t_cursor *cursor, char code_arg)
{
	char	step;
	char	i;

	step = 2;
	i = 6;
	while (i)
	{
		if (((code_arg >> i) & 3) == REG_CODE)
			step++;
		else if (((code_arg >> i) & 3) == IND_CODE)
			step += IND_SIZE;
		else if (((code_arg >> i) & 3) == DIR_CODE)
			step += (DIR_SIZE - (2 * g_op_tab[cursor->op_code].tdir_size));
		else if (i == 6 && (((code_arg >> 6) & 3) == 0))
		{
			cursor->step = 1;
			cursor->cycles2go = 0;
			return ;
		}
		i -= 2;
	}
	cursor->step = step;
	cursor->cycles2go = g_op_tab[cursor->op_code].cycles2go;
}
*/

static void	initial_read_cursor(t_cursor *cursor, char *arena)
{
	char	code_arg;

	cursor->op_code = arena[cursor->pos];
	if (!(cursor->op_code > 0 && cursor->op_code < 17))
	{
		cursor->step = 1;
		cursor->cycles2go = 0;
	}
	else
	{
		if (g_op_tab[cursor->op_code].code_args)
			code_arg = arena[(cursor->pos + 1) % MEM_SIZE];
		else
		{
			cursor->step = 1 + (DIR_SIZE -\
			(2 * g_op_tab[cursor->op_code].tdir_size));
		}
		cursor->cycles2go = g_op_tab[cursor->op_code].cycles2go;
	}
}

static void calculate_cycle_to_die(t_vm *vm)
{
	if (vm->num_live_op >= NBR_LIVE || vm->checks_without_dec_cycle2die == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks_without_dec_cycle2die = 0;
	}
	else
		vm->checks_without_dec_cycle2die += 1;
}

static void	check_cursors(t_vm *vm)
{
	t_cursor	*temp;

	temp = vm->cursors;
	while (temp)
	{
		if (((vm->cycles - temp->cycle_live) >= vm->cycles_to_die) || vm->cycles_to_die <= 0)
			kill_cursor(&vm->cursors, temp);
		temp = temp->next;
	}
	calculate_cycle_to_die(vm);
}

t_bool		validation_arg(char op_code, t_arg_type type, char num_arg)
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

static char	check_op_code_and_type_args(t_cursor *cursor, char *arena)
{
	unsigned char	code;
	char	step;
	char	i;
	char	exec;
	char	arg_code;

	i = 0;
	step = 2;
	exec = 1;
	if (g_op_tab[cursor->op_code].code_args)
	{
		code = arena[(cursor->pos + 1) % MEM_SIZE];
		while (i < g_op_tab[cursor->op_code].num_args)
		{
			arg_code = (code >> (6 - (2 * i)) & 3);
			if(arg_code == REG_CODE)
				step++;
			else if (arg_code == DIR_CODE)
				step += (4 - (2 * g_op_tab[cursor->op_code].tdir_size));
			else if (arg_code == IND_CODE)
				step += IND_SIZE;
			exec = validation_arg(cursor->op_code, arg_code, i) ? exec : 0;
			i++;
		}
		cursor->step = step;
	}
	return (exec);
}

void	cycle(t_vm *vm)
{
	t_cursor	*temp;

	while (vm->cursors)
	{
		temp = vm->cursors;
		while (temp)
		{
			temp->cycles2go -= 1;
			if (!temp->cycles2go)
			{
				if (temp->op_code && check_op_code_and_type_args(temp, vm->arena))
					g_operation[temp->op_code](vm, temp);
				temp->exec = TRUE;
				temp->pos = (temp->pos + temp->step) % MEM_SIZE;
				initial_read_cursor(temp, vm->arena);
			}
			temp = temp->next;
		}
		vm->cycles += 1;
		vm->cycles_from_last_check += 1;
		 if(vm->cycles_from_last_check >= vm->cycles_to_die)
		{
			check_cursors(vm);
			vm->cycles_from_last_check = 0;
		}
	}
}
