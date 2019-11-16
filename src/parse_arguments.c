/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/16 17:14:20 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[];

static int		possible_arg(char arg_type, char mask)
{
	if (arg_type == T_REG && !(((mask >> 4) & T_REG) ^ T_REG))
		return (1);
	else if (arg_type == T_DIR && !(((mask >> 2) & T_DIR) ^ T_DIR))
		return (1);
	else if (arg_type == T_IND && !((mask & 3) ^ 3))
		return (1);
	return (0);
}

static int		get_type_argument(char *arg)
{
	int i;

	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
		return(T_DIR);
	if (arg[i] == REG_CHAR)
		return (T_REG);
	if (ft_isdigit(arg[i]) || arg[i] == LABEL_CHAR || arg[i] == '-')
		return(T_IND);
	return(0);
}

static t_instr	*last_instruction(t_instr *instr)
{
	while (instr->next)
		instr = instr->next;
	return (instr);
}

static int		label2value(t_arg *arg, t_champ *champ, int offset)
{
	int		value;
	t_label		*tmp;
	t_instr		*last_instr;

	tmp = champ->labels;
	while(tmp)
	{
		if (!ft_strcmp(arg->str + offset, tmp->name))
		{
			value = tmp->offset;
			break;
		}
		tmp = tmp->next;
	}
	if (arg->type == T_IND)
	{
		last_instr = last_instruction(champ->instr);
		value -= (last_instr->offset + last_instr->instr_size);
	}
	return (value);
}

static void		get_arg_value(t_arg *arg, t_champ *champ)
{
	int value;
	int i;
	char	label;

	i = 0;
	if (arg->type == T_DIR || arg->type == T_REG)
		i += 1;
	label = arg->str[i] == LABEL_CHAR ? 1 : 0;
	arg->value = label ? label2value(arg, champ, i + 1) : ft_atoi(arg->str + i);

}

static int		add_argument(t_champ *champ, t_arg *arg, char *filedata, int i)
{
	int		valid;
	char	*str_before_trim;

	valid = valid_argument(&filedata[i], arg->type, champ->labels);
	if (valid)
	{
		if (!(str_before_trim = ft_strsub(filedata, i, valid)))
			ft_exit(&champ, MALLOC_FAILURE);
		if (!(arg->str = ft_strtrim(str_before_trim)))
			ft_exit(&champ, MALLOC_FAILURE);
		ft_strdel(&str_before_trim);
		get_arg_value(arg, champ);
	}
	else
		error_manager(&champ, filedata, &filedata[i], T_NONE);
	i = skip_spaces(filedata, i + valid);
	if (!isseparator(filedata[i++]))
		error_manager(&champ, filedata, &filedata[i], T_SEPARATOR);
	i = skip_spaces(filedata, i);
	return (i);
}

int			parse_arguments(t_champ *champ, t_instr *instruct,\
			char *filedata, int i)
{
	int		j;
	char	arg_type;

	j = 0;
	while (j < instruct->num_args)
	{
		arg_type = get_type_argument(&filedata[i]);
		if (possible_arg(arg_type, g_op_tab[instruct->code].args[j]))
		{
			instruct->args[j].type = arg_type;
			i = add_argument(champ, &instruct->args[j], filedata, i);
		}
		else
			invalid_parameter(&champ, &filedata[i], instruct, j);
		++j;
	}
	if (get_type_argument(&filedata[i]))
		invalid_parameter(&champ, &filedata[i], instruct, j);
	while (ft_isspace(filedata[i]))
		++i;
	return (i);
}

void		print_args(t_arg *args, int num)
{
	int		i;

	i = 0;
	ft_printf("\nARGS\n");
	ft_printf("__________________________________________________________\n");
	ft_printf("|       type       |       str        |       value      |\n");
	while (i < num)
	{
		ft_printf("| %16d | %16s | %16d |\n", args[i].type, args[i].str,\
		(short)args[i].value);
		i++;
	}
	ft_printf("|________________________________________________________|\n");
}
