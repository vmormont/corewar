/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/14 19:43:49 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int 	get_instruct_code(char *name, t_op *op_tab)
{
	int i;
	
	i = 1;
	while (i <= NUMBER_OF_INSTR)
	{
		if (!ft_strncmp(op_tab[i].name, name, ft_strlen(op_tab[i].name)))
			return (i);
		++i;
	}
	return (0);
}

static int 	get_type_arg(char *arg)
{
	int i;
	
	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
		return(T_DIR);
	if (arg[i] == 'r')
		return (T_REG);
	if (ft_isdigit(arg[i]))
		return(T_IND);
	return(0);
}

static int		get_instr(t_champ *champ, char *filedata, int i)
{
	int 		valid_code;
	t_instr		*instruct;
	//мы находимся всегда в начале команды
	
	//променяем валидность названия инструкции
	valid_code = get_instruct_code(&filedata[i], champ->op_tab);
	
	//создаем новую инструкцию
	if (valid_code)
	{
		if (!(instruct = new_instruct(&champ->op_tab[valid_code])))
			ft_exit(&champ, MALLOC_FAILURE);
	}
	else
		lexical_error(&champ, filedata, &filedata[i]);
	
	champ->instr = add_instr2end(champ->instr, instruct);
	
	//сдвигаем индекс на длину команды
	//i += ft_strlen(champ->op_tab[valid_code].name);
	
	//если после команды нет пробельного символа вызываем ошибку
	if (!ft_isspace(filedata[i]))
		lexical_error(&champ, filedata, &filedata[i]);
	i += skip_spaces(filedata, i);
	//запускаем парсинг аргументов
	i += get_arguments(champ, filedata, i);
	return (i);
}

void		parse_instr(t_champ *champ, char *filedata, int i)
{
	int j;

	j = 0;
	while (filedata[i])
	{
		// вначале цикла мы находимся всегда вначале строки

		// так как лейблов подряд может быть несколько
		// мы добавляем их все
		while (j != i)
		{
			j = i;
			i = detect_label(champ, filedata, i);
		}

		//тут должна быть функция парсинга инструкции
		//while (filedata[i] != '\n')
		//	++i;
		i += get_instr (champ, filedata, i);

		//переходим по пробельным символам на следующую строку
		while (ft_isspace(filedata[i]) && filedata[i] != '\n')
			++i;
		++i;
		//считываем аргументы команды
	}
	while (champ->labels)
	{
		ft_printf("label = %s, offset = %u\n",\
		champ->labels->name, champ->labels->offset);
		champ->labels = champ->labels->next;
	}
}