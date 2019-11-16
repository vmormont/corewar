/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/16 17:17:06 by astripeb         ###   ########.fr       */
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

static int	define_instruct_offset(t_instr *instr)
{
	t_instr		*tmp;

	if (!instr)
		return (0);
	else
	{
		while (instr->next)
			instr = instr->next;
		return (instr->offset + instr->instr_size);
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
		error_manager(&champ, filedata, &filedata[i], T_NONE);

	i = skip_spaces(filedata, i);

	//запускаем парсинг аргументов
	i = parse_arguments(champ, instruct, filedata, i);
	instruct->instr_size = define_instruct_size(instruct);
	instruct->offset = define_instruct_offset(champ->instr);
	add_instr2end(&champ->instr, instruct);
	return (i);
}

int			parse_instruction(t_champ *champ, char *filedata, int i)
{
	t_instr	*temp;

	while (filedata[i])
	{
		// вначале цикла мы находимся всегда вначале строки
		i = skip_spaces(filedata, i);
		// так как лейблов подряд может быть несколько
		// мы добавляем их все
		i = parse_label(champ, filedata, i);
		i = get_instruction(champ, filedata, i);
	}
	return (i);
}
