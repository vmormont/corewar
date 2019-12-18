/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:35:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/18 17:45:52 by pcredibl         ###   ########.fr       */
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

	id_winner = vm->winner;
	winner = get_champ_by_id(vm->champs, id_winner);
	if (!vm->options.terminal)
		ft_printf("Contestant %d, \"%s\", has won !\n", -id_winner, winner->name);
	else
	{
	mvprintw(23 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"The winner is :\t");
	color_set(-id_winner, NULL);
	printw("%s", winner->name);
	color_set(WHITE_TEXT, NULL);
	mvprintw(25 + (4 * vm->num_of_champs) + 7, (3 * DUMP_COLUMNS) + 8,\
	"Press any key to finish !!!");
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
