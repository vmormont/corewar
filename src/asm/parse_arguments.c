/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:26:50 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 17:40:17 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_type_argument(char *arg)
{
	int i;

	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
		return (T_DIR);
	if (arg[i] == REG_CHAR)
		return (T_REG);
	if (ft_isdigit(arg[i]) || arg[i] == LABEL_CHAR || arg[i] == '-')
		return (T_IND);
	return (0);
}

static int	add_argument(t_champ *champ, t_instr *instruct, int num_arg, int i)
{
	int		valid;
	char	*str_before_trim;

	valid = valid_argument(&champ->data[i], instruct->args[num_arg].type);
	if (!valid)
		error_manager(&champ, &champ->data[i], T_NONE);
	if (!(str_before_trim = ft_strsub(champ->data, i, valid)))
	{
		del_one_instr(&instruct);
		ft_exit(&champ, MALLOC_FAILURE);
	}
	if (!(instruct->args[num_arg].str = ft_strtrim(str_before_trim)))
	{
		del_one_instr(&instruct);
		ft_strdel(&str_before_trim);
		ft_exit(&champ, MALLOC_FAILURE);
	}
	ft_strdel(&str_before_trim);
	i = skip_spaces(champ->data, i + valid);
	return (i);
}

int			parse_arguments(t_champ *champ, t_instr *instruct,\
			char *filedata, int i)
{
	int		j;
	char	arg_type;

	j = 0;
	while (42)
	{
		if (!(arg_type = get_type_argument(&filedata[i])))
			error_manager(&champ, &filedata[i], T_NONE);
		if (!possible_arg(instruct->code, j, arg_type))
			invalid_parameter(&champ, &filedata[i], instruct, j);
		instruct->args[j].type = arg_type;
		i = add_argument(champ, instruct, j, i);
		if (filedata[i] != SEPARATOR_CHAR)
			break ;
		i = skip_spaces(filedata, i + 1);
		++j;
	}
	if (filedata[i] != '\n')
		error_manager(&champ, &filedata[i], T_NONE);
	while (ft_isspace(filedata[i]))
		++i;
	return (i);
}
