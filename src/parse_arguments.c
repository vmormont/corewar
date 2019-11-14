/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/15 01:07:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	possible_arg(char arg_type, char mask)
{
	if (arg_type == T_REG && !(((mask >> 4) & T_REG) ^ T_REG))
		return (1);
	else if (arg_type == T_DIR && !(((mask >> 2) & T_DIR) ^ T_DIR))
		return (1);
	else if (arg_type == T_IND && !((mask & 3) ^ 3))
		return (1);
	return (0);
}

int get_type_argument(char *arg)
{
	int i;

	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
		return(T_DIR);
	if (arg[i] == REG_CHAR)
		return (T_REG);
	if (ft_isdigit(arg[i]) || arg[i] == LABEL_CHAR)
		return(T_IND);
	return(0);
}

int	valid_label(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == LABEL_CHAR)
	{
		while (arg[++i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
		{
			if (!ft_islabel(arg[i], LABEL_CHARS))
				return (0);
		}
	}
	return (i);
}

int	valid_direct(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == DIRECT_CHAR)
	{
		if (arg[++i] == LABEL_CHAR)
		{
			if (!(i += valid_label(&arg[i], label)))
				return (0);
		}
		else
		{
			while (arg[i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
			{
				if (!ft_isdigit(arg[i]))
					return (0);
				++i;
			}
		}
	}
	return (i);
}

int	valid_indirect(char *arg, t_label *label)
{
	int i;

	i = 0;
	if (arg[i] == LABEL_CHAR)
	{
		if (!(i = valid_label(&arg[i], label)))
			return (0);
	}
	else
	{
		while (arg[i] != SEPARATOR_CHAR)
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			++i;
		}
	}
	return (i);
}

int	valid_register(char *arg)
{
	int i;
	int	reg_num;

	i = 0;
	if (arg[i++] != REG_CHAR)
		return (0);
	reg_num = ft_atoi(&arg[i]);
	if (reg_num < MIN_REG && reg_num > MAX_REG)
		return (0);
	while (arg[i] && arg[i] != SEPARATOR_CHAR && arg[i] != '\n')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		++i;
	}
	return (i);
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
	}
	else
		lexical_error(&champ, filedata, &filedata[i]);
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
			lexical_error(&champ, filedata, &filedata[i]);
		}
		++j;
		if (j < instruct->num_args && filedata[i++] != SEPARATOR_CHAR)
			lexical_error(&champ, filedata, &filedata[--i]);
		i = skip_spaces(filedata, i);
	}
	++i;
	champ->instr = add_instr2end(champ->instr, instruct);
	return (i);
}
