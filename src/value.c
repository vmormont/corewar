/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:27:03 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/16 17:17:38 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		label2value(char *title, t_label *labels, char arg_type,\
				int offset)
{
	int		value;

	value = 0;
	while (labels)
	{
		if (!ft_strcmp(title, labels->name))
		{
			if (arg_type == T_DIR)
				value = labels->offset;
			else if (arg_type == T_IND)
				value = labels->offset - offset;
		}
		labels = labels->next;
	}
	return(value);
}

static void		browse_args(t_instr *instr, t_label *labels)
{	int			i;
	int			k;
	t_label		*tmp;

	i = -1;
	while(++i < instr->num_args)
	{
		k = 0;
		if (instr->args[i].type == T_DIR || instr->args[i].type == T_REG)
			k++;
		if (instr->args[i].str[k] == LABEL_CHAR)
			instr->args[i].value = label2value(instr->args[i].str + k + 1,\
			labels,	instr->args[i].type, instr->offset);
		else
			instr->args[i].value = ft_atoi(instr->args[i].str + k);
	}
}

void			get_arg_value(t_champ *champ)
{
	t_instr		*tmp;

	tmp = champ->instr;
	while (tmp)
	{
		browse_args(tmp, champ->labels);
		tmp = tmp->next;
	}

}
