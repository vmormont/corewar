/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/16 14:03:06 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[];

static int	define_instruct_size(t_instr *instr)
{
	int		size;
	int		i;

	size = 1 + instr->code_args;
	i = 0;
	while (i < instr->num_args)
	{
		if (instr->args[i].type == T_REG)
			size += 1;
		if (instr->args[i].type == T_IND)
			size += 2;
		if (instr->args[i].type == T_DIR)
			size += instr->tdir_size;
		++i;
	}
	return (size);
}

static int	define_instruct_offset(t_instr *begin)
{
	t_instr		*tmp;

	if (!begin)
		return (0);
	else
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		return (tmp->offset + tmp->instr_size);
	}
}

static int	get_instruct_code(char *name)
{
	int i;
	int	code;
	int name_len;

	i = 1;
	code = 0;
	while (i <= NUMBER_OF_INSTR)
	{
//		ft_printf("name = %s\n", op_tab[i].name);
		name_len = ft_strlen(g_op_tab[i].name);
		if (!ft_strncmp(g_op_tab[i].name, name, name_len))
		{
			if (ft_isspace(name[name_len]))
				code = i;
		}
		++i;
	}
	return (code);
}

static int	get_instruction(t_champ *champ, char *filedata, int i)
{
	int 		valid_code;
	t_instr		*instruct;

	//мы находимся всегда в начале команды
	//променяем валидность названия инструкции
	valid_code = get_instruct_code(&filedata[i]);

	//создаем новую инструкцию
	if (valid_code)
	{
		if (!(instruct = new_instruct(&g_op_tab[valid_code])))
			ft_exit(&champ, MALLOC_FAILURE);
		//сдвигаем индекс на длину команды
		i += ft_strlen(g_op_tab[valid_code].name);
	}
	else
		error_manager(&champ, filedata, &filedata[i], T_INSTRUCTION);

	//если после команды нет пробельного символа вызываем ошибку
	if (!ft_isspace(filedata[i]) || filedata[i] == '\n')
		error_manager(&champ, filedata, &filedata[i], T_INSTRUCTION);

	i = skip_spaces(filedata, i);

	//запускаем парсинг аргументов
	i = parse_arguments(champ, instruct, filedata, i);
	instruct->instr_size = define_instruct_size(instruct);
	instruct->offset = define_instruct_offset(champ->instr);
	return (i);
}

int			parse_instruction(t_champ *champ, char *filedata, int i)
{
	int j;
	t_instr	*temp;

	j = 0;
	while (filedata[i])
	{
		// вначале цикла мы находимся всегда вначале строки
		// так как лейблов подряд может быть несколько
		// мы добавляем их все
		while (j != i)
		{
			i = skip_spaces(filedata, i);
			j = i;
			i = parse_label(champ, filedata, i);
		}
		// парсим инструкцию
		i = get_instruction(champ, filedata, i);
	}
/*
	ft_printf("\nNAME = %s\nCOMMENT = %s\n\n", champ->name, champ->comment);
	print_label(champ->labels);
	print_instruct(champ->instr);
	temp = champ->instr;
	while (temp)
	{
		print_args(temp->args, temp->num_args);
		temp = temp->next;
	}
*/
	return (i);
}
