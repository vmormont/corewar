/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/16 14:18:45 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	possible_arg(char arg_type, char mask)
{
	if (arg_type == T_REG && !(((mask >> 4) & T_REG) ^ T_REG))
		return (1);
	else if (arg_type == T_DIR && !(((mask >> 2) & T_DIR) ^ T_DIR))
		return (1);
	else if (arg_type == T_IND && !((mask & 3) ^ 3))
		return (1);
	return (0);
}

static int	get_type_argument(char *arg)
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

static t_instr *last_instruction(t_instr *instr)
{
	while (instr->next)
		instr = instr->next;
	return (instr);
}

static int	label2value(t_arg *arg, t_champ *champ, int offset)
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

static void	get_arg_value(t_arg *arg, t_champ *champ)
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

int	add_argument(t_champ *champ, t_arg *arg, char *filedata, int i)
{
	int valid;

	if (arg->type == T_DIR)
		valid = valid_direct(&filedata[i], champ->labels);
	else if (arg->type == T_IND)
		valid = valid_indirect(&filedata[i], champ->labels);
	else if (arg->type == T_REG)
		valid = valid_register(&filedata[i]);
	if (valid)
	{
		if (!(arg->str = ft_strsub(filedata, i, valid)))
			ft_exit(&champ, MALLOC_FAILURE);
		get_arg_value(arg, champ);
	}
	else
		error_manager(&champ, filedata, &filedata[i]);
	return (i + valid);
}

int	parse_arguments(t_champ *champ, t_instr *instruct, char *filedata, int i)
{
	int		j;
	char	arg_type;

	//мы находимся на первом не 'пробельном' символе после инструкции
	j = 0;
	while (j < instruct->num_args)
	{
		//получаем тип аргумента
		arg_type = get_type_argument(&filedata[i]);

		//проверяем валидность аргумента
		if (possible_arg(arg_type, champ->op_tab[instruct->code].args[j]))
		{
			instruct->args[j].type = arg_type;
			i = add_argument(champ, &instruct->args[j], filedata, i);
		}
		else
		{
			del_one_instr(&instruct);
			error_manager(&champ, filedata, &filedata[i]);
		}
		++j;
		if (j < instruct->num_args && filedata[i++] != SEPARATOR_CHAR)
			error_manager(&champ, filedata, &filedata[--i]);
		i = skip_spaces(filedata, i);
	}
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
		ft_printf("| %16d | %16s | %16d |\n", args[i].type, args[i].str, (short)args[i].value);
		i++;
	}
	ft_printf("|________________________________________________________|\n");
}
