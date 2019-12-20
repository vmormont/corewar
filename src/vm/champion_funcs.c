/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:35:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/20 16:19:54 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ			*create_new_champ(t_header *head, void *code)
{
	t_champ *champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero((void*)champ, sizeof(t_champ));
	if (!(champ->name = ft_strdup(head->prog_name))\
	|| !(champ->comment = ft_strdup(head->comment))\
	|| !(champ->code = ft_strnew(head->prog_size)))
	{
		del_one_champion(&champ);
		return (NULL);
	}
	ft_memcpy(champ->code, code, head->prog_size);
	champ->code_size = head->prog_size;
	champ->magic = head->magic;
	return (champ);
}

void			del_one_champion(t_champ **champ)
{
	if (champ && *champ)
	{
		(*champ)->next = NULL;
		ft_memdel((void*)&(*champ)->name);
		ft_memdel((void*)&(*champ)->comment);
		ft_memdel((void*)&(*champ)->code);
		ft_memdel((void*)champ);
	}
}

void			del_champions(t_champ **begin)
{
	t_champ	*first;
	t_champ	*second;

	if (begin && *begin)
	{
		first = *begin;
		while (first)
		{
			second = first;
			first = first->next;
			del_one_champion(&second);
		}
		*begin = NULL;
	}
}

void			add_champion2end(t_champ **begin, t_champ *champ, int id)
{
	t_champ	*temp;

	if (begin)
	{
		champ->id = id;
		if (!*begin)
		{
			*begin = champ;
		}
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = champ;
		}
	}
}

void			announce_winner(t_vm *vm)
{
	int		id_winner;
	t_champ	*winner;

	nodelay(stdscr, FALSE);
	id_winner = vm->winner;
	winner = get_champ_by_id(vm->champs, id_winner);
	if (!vm->options.terminal)
		ft_printf("Contestant %d, \"%s\", has won !\n", -id_winner, winner->name);
	else
	{
		nodelay(vm->visual->arena, FALSE);
		nodelay(vm->visual->menu, FALSE);
		mvwprintw(vm->visual->menu, 29 + (4 * vm->num_of_champs), 2,\
		"The winner is : ");
		wcolor_set(vm->visual->menu, -id_winner, NULL);
		wprintw(vm->visual->menu, "%s", winner->name);
		wcolor_set(vm->visual->menu, WHITE_TEXT, NULL);
		mvwprintw(vm->visual->menu, 31 + (4 * vm->num_of_champs), 2,\
		"Press any key to finish !!!");
		wrefresh(vm->visual->menu);
		getch();
	}
}

void			print_champs(t_champ *champ)
{
	ft_printf("__________________________________\n");
	while (champ)
	{
		ft_printf("id      = %d\n", champ->id);
		ft_printf("magic   = %x\n", champ->magic);
		ft_printf("name    = %s\n", champ->name);
		ft_printf("comment = %s\n", champ->comment);
		ft_printf("size    = %d\n", champ->code_size);
		ft_printf("----------------------------------\n");
		champ = champ->next;
	}
}
