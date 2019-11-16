/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/16 17:02:26 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[];

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

int	add_argument(t_champ *champ, t_arg *arg, char *filedata, int i)
{
	int		valid;
	char	*str_before_trim;

	if (arg->type == T_DIR)
		valid = valid_direct(&filedata[i], champ->labels);
	else if (arg->type == T_IND)
		valid = valid_indirect(&filedata[i], champ->labels);
	else if (arg->type == T_REG)
		valid = valid_register(&filedata[i]);
	if (valid)
	{
		if (!(str_before_trim = ft_strsub(filedata, i, valid)))
			ft_exit(&champ, MALLOC_FAILURE);
		if (!(arg->str = ft_strtrim(str_before_trim)))
			ft_exit(&champ, MALLOC_FAILURE);
		ft_strdel(&str_before_trim);
		//get_arg_value(arg, champ);
	}
	else
		error_manager(&champ, filedata, &filedata[i], T_NONE);
	i = skip_spaces(filedata, i + valid);
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
			error_manager(&champ, filedata, &filedata[i], T_NONE);
		i = skip_spaces(filedata, i);
		if (!isseparator(filedata[i++]))
		{
			del_one_instr(&instruct);
			error_manager(&champ, filedata, &filedata[i], T_NONE);
		}
		++j;
		i = skip_spaces(filedata, i);
	}
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
		ft_printf("| %16d | %16s | %16d |\n", args[i].type, args[i].str, (short)args[i].value);
		i++;
	}
	ft_printf("|________________________________________________________|\n");
}
