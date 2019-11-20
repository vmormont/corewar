/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:27:03 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 13:33:52 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_label	*get_label(t_label *label, char *label_name)
{
	while (label)
	{
		if (!ft_strcmp(label_name, label->name))
			return (label);
		label = label->next;
	}
	return (NULL);
}

/*
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
	return (value);
}
*/

static void		browse_arguments(t_champ *champ, t_instr *instr)
{
	int			i;
	int			k;
	t_label		*label;

	i = -1;
	while (++i < instr->num_args)
	{
		k = 0;
		if (instr->args[i].type == T_DIR || instr->args[i].type == T_REG)
			k = 1;
		if (instr->args[i].str[k] == LABEL_CHAR)
		{
			label = get_label(champ->labels, instr->args[i].str + k + 1);
			if (!label)
				error_manager(&champ,\
				ft_strstr(champ->data, instr->args[i].str), T_NO_LABEL);
			if (instr->args[i].type == T_DIR)
				instr->args[i].value = label->offset - instr->offset;
			else if (instr->args[i].type == T_IND)
				instr->args[i].value = label->offset - instr->offset;
		}
		else
			instr->args[i].value = ft_atoi(instr->args[i].str + k);
	}
}

void			assign_arguments_values(t_champ *champ)
{
	t_instr		*instruct;

	instruct = champ->instr;
	while (instruct)
	{
		browse_arguments(champ, instruct);
		instruct = instruct->next;
	}
}
