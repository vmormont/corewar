/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/23 17:36:08 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	if (!instr)
		return (0);
	else
	{
		while (instr->next)
			instr = instr->next;
		return (instr->offset + instr->instr_size);
	}
}

static int	get_instruction(t_champ *champ, char *filedata, int i)
{
	int			valid_code;
	t_instr		*instruct;

	valid_code = get_instruct_code(&filedata[i]);
	if (!valid_code)
		error_manager(&champ, &filedata[i], T_INSTRUCTION);
	if (!(instruct = new_instruct(get_op_struct(valid_code))))
		ft_exit(&champ, MALLOC_FAILURE);
	i += ft_strlen(get_op_name(valid_code));
	if (!isseparator(filedata[i]) || filedata[i] == '\n')
		error_manager(&champ,\
		&filedata[i - ft_strlen(get_op_name(valid_code))], T_NONE);
	i = skip_spaces(filedata, i);
	i = parse_arguments(champ, instruct, filedata, i);
	instruct->instr_size = define_instruct_size(instruct);
	instruct->offset = define_instruct_offset(champ->instr);
	add_instr2end(&champ->instr, instruct);
	return (i);
}

void		asm_file_parser(t_champ *champ, char *filename)
{
	int		i;

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
}
