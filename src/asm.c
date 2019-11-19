/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/19 20:49:29 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_champ		*champ;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	lexical_analizer(champ, argv[1]);
	create_cor_file(argv[1], champ);
	free_champ(&champ);
	return (0);
}

void		lexical_analizer(t_champ *champ, char *filename)
{
	int		i;
	t_instr *temp;

	champ->data = get_clean_data_from_file(champ, filename);
	i = parse_name(champ, champ->data);
	i = parse_instruction(champ, champ->data, i);
	get_arg_value(champ);
	ft_printf("\nNAME = %s\nCOMMENT = %s\n\n", champ->name, champ->comment);
	print_label(champ->labels);
	print_instruct(champ->instr);
	temp = champ->instr;
	while (temp)
	{
		print_args(temp->args, temp->num_args);
		temp = temp->next;
	}
}
