/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:54 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/16 15:51:02 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	t_champ		*champ;

	argc == 1 ? ft_exit(NULL, USAGE) : 0;
	champ = create_champ();
	lexical_analizer(champ, argv[1]);
	free_champ(&champ);
	return (0);
}

void		lexical_analizer(t_champ *champ, char *filename)
{
	int		i;
	char	*filedata;
	t_instr *temp;

	filedata = get_clean_data_from_file(champ, filename);
	i = parse_name(champ, filedata);
	i = parse_instruction(champ, filedata, i);
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
	ft_strdel(&filedata);
}
