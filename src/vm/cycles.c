/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:46:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/25 20:27:24 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

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


static void	read_cursor(t_cursor *cursor, char *arena)
{
	char	code_arg;

	cursor->op_code = arena[cursor->pos];
	if(!(cursor->op_code > 0 && cursor->op_code < 17))
	{
		cursor->step = 1;
		cursor->cycles2go = 0;
	}
	else
	{
		if (g_op_tab[cursor->op_code].code_args)
		{
			code_arg = arena[cursor->pos + 1];
			define_step_and_time_cursor(cursor, code_arg);
		}
		else
		{
			cursor->step = 1 + (DIR_SIZE -\
			(2 * g_op_tab[cursor->op_code].tdir_size));
			cursor->cycles2go = g_op_tab[cursor->op_code].cycles2go;	
		}
	}
	ft_printf("op_code = %d\nstep = %d\ncycle2go = %d\n", cursor->op_code, cursor->step, cursor->cycles2go);
	ft_printf("------------------------------\n");
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
		if (((vm->cycles - temp->cycle_live) > vm->cycles_to_die) || vm->cycles_to_die <= 0)
			kill_cursor(&vm->cursors, temp);
		temp = temp->next;
	}
	calculate_cycle_to_die(vm);
}


void	cycle(t_vm *vm)
{
	t_cursor	*temp;
	int			i;

	i = 0;
	while (i < 50)
	{
		temp = vm->cursors;
		while (temp)
		{
			temp->cycles2go -= 1;
			if (!temp->cycles2go)
				temp->cycles2go -= 0;
				//exec_op(temp);
			else if (temp->cycles2go == -1)
				temp->pos += temp->step; 
			else if (temp->cycles2go == -2)
				read_cursor(temp, vm->arena);		
			//ft_printf("time to exec = %d\n", temp->cycles2go);
			temp = temp->next;
		}
		vm->cycles += 1;
		/* if(что-то там)
			check_cursors(vm);*/
		i++;
	}
	
}