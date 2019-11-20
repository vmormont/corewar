/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_to_stdo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:35:25 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/20 20:00:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

static int	get_exec_code_size(t_instr *instruct)
{
	while (instruct->next)
		instruct = instruct->next;
	return (instruct->offset + instruct->instr_size);
}

static void	print_byte_arg_values(t_instr *instruct)
{
	int		i;
	t_arg	*args;

	i = 0;
	args = instruct->args;
	while (i < instruct->num_args)
	{
		if (args[i].type == T_REG)
			ft_printf("%-4u              ", args[i].value);
		else if (args[i].type == T_IND\
		|| (args[i].type == T_DIR && instruct->tdir_size == 2))
		{
			ft_printf("%-4u%-4u          ",\
			(args[i].value >> 8) & 0xFF, args[i].value & 0xFF);
		}
		else if (args[i].type == T_DIR)
		{
			ft_printf("%-4u%-4u%-4u%-4u  ",\
			(args[i].value >> 24) & 0xFF, (args[i].value >> 16) & 0xFF,\
			(args[i].value >> 8) & 0xFF, args[i].value & 0xFF);
		}
		++i;
	}
	ft_printf("\n");
}

static void	print_arg_values(t_instr *instruct)
{
	int		i;
	t_arg	*args;

	i = 0;
	args = instruct->args;
	while (i < instruct->num_args)
	{
		ft_printf("%-18d", args[i].value);
		++i;
	}
	ft_printf("\n");
}

static void	print_instr(t_instr *instruct)
{
	int		i;
	t_arg	*args;

	ft_printf("%-5u(%-3u) :        %-10s",\
	instruct->offset, instruct->instr_size, g_op_tab[instruct->code].name);
	i = 0;
	args = instruct->args;
	while (i < instruct->num_args)
	{
		ft_printf("%-18s", args[i].str);
		++i;
	}
	ft_printf("\n                    %-4u", instruct->code);
	if (instruct->code_args)
		ft_printf("%-6u", define_code_args(instruct) & 0xFF);
	else
		ft_printf("      ");
	print_byte_arg_values(instruct);
	ft_printf("                    %-4u", instruct->code);
	if (instruct->code_args)
		ft_printf("%-6u", define_code_args(instruct) & 0xFF);
	else
		ft_printf("      ");
	print_arg_values(instruct);
	ft_printf("\n");
}

void		dump_to_stdout(t_champ *champ)
{
	t_instr	*instruct;
	t_label	*label;

	instruct = champ->instr;
	label = champ->labels;
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", get_exec_code_size(instruct));
	ft_printf("Name : \"%s\"\n", champ->name);
	ft_printf("Comment : \"%s\"\n\n", champ->comment);
	while (instruct)
	{
		if (label && label->offset == instruct->offset)
		{
			ft_printf("%-11u:    %s:\n", label->offset, label->name);
			label = label->next;
			continue ;
		}
		print_instr(instruct);
		instruct = instruct->next;
	}
	while (label)
	{
		ft_printf("%-11u:    %s:\n", label->offset, label->name);
		label = label->next;
	}
}
