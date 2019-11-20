/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/20 13:51:57 by astripeb         ###   ########.fr       */
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
			code = i;
		++i;
	}
	return (code);
}

static int	get_instruction(t_champ *champ, char *filedata, int i)
{
	int			valid_code;
	t_instr		*instruct;

	//мы находимся всегда в начале команды
	//променяем валидность названия инструкции
	valid_code = get_instruct_code(&filedata[i]);

	//если инструкции нет, сообщаем об ошибке
	if (!valid_code)
		error_manager(&champ, &filedata[i], T_INSTRUCTION);

	//создаем новую инструкцию
	if (!(instruct = new_instruct(&g_op_tab[valid_code])))
		ft_exit(&champ, MALLOC_FAILURE);

	//сдвигаем индекс на длину команды
	i += ft_strlen(g_op_tab[valid_code].name);

	//если после команды нет явного, разделяющего символа вызываем ошибку
	if (!isseparator(filedata[i]) || filedata[i] == '\n')
		error_manager(&champ,\
		&filedata[i - ft_strlen(g_op_tab[valid_code].name)], T_NONE);
	i = skip_spaces(filedata, i);

	//запускаем парсинг аргументов
	i = parse_arguments(champ, instruct, filedata, i);

	//добавляем размер инструккци и ее смещение относительно начала кода
	instruct->instr_size = define_instruct_size(instruct);
	instruct->offset = define_instruct_offset(champ->instr);

	//добавляем в список инструкции
	add_instr2end(&champ->instr, instruct);
	return (i);
}

void		asm_file_parser(t_champ *champ, char *filename)
{
	int		i;
	t_instr *temp;

	champ->data = get_clean_data_from_file(champ, filename);
	i = parse_name(champ, champ->data);
	while (champ->data[i])
	{
		i = skip_spaces(champ->data, i);
		i = parse_label(champ, champ->data, i);
		if (champ->data[i])
			i = get_instruction(champ, champ->data, i);
	}
	if (!champ->instr)
		error_manager(&champ, &champ->data[i], T_END);
	assign_arguments_values(champ);
/*
	//УДОЛИТЬ!
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
}
