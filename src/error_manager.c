/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:13:47 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/19 18:38:19 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[];

static int	get_token_type(char *arg)
{
	int i;

	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
	{
		if (arg[++i] == LABEL_CHAR)
			return (T_DIR_LABEL);
		return (T_DIR);
	}
	if (arg[i] == REG_CHAR)
		return (T_REG);
	if (ft_isdigit(arg[i]))
		return (T_IND);
	if (arg[i] == '\n')
		return (T_ENDLINE);
	if (arg[i] == SEPARATOR_CHAR)
		return (T_SEPARATOR);
	if (isinstruct(arg))
		return (T_INSTRUCTION);
	if (arg[i] == LABEL_CHAR)
		return (T_IND_LABEL);
	if (islabel(arg))
		return (T_LABEL);
	return (0);
}

static void	print_token(char token)
{
	if (token == T_DIR || token == T_DIR_LABEL)
		ft_fprintf(2, " DIRECT");
	else if (token == T_IND || token == T_IND_LABEL)
		ft_fprintf(2, " INDIRECT");
	else if (token == T_REG)
		ft_fprintf(2, " REGISTER");
	else if (token == T_ENDLINE)
		ft_fprintf(2, " ENDLINE\n");
	else if (token == T_SEPARATOR)
		ft_fprintf(2, " SEPARATOR");
	else if (token == T_INSTRUCTION)
		ft_fprintf(2, " INSTRUCTION");
	else if (token == T_LABEL)
		ft_fprintf(2, " LABEL");
	else if (token == T_NAME)
		ft_fprintf(2, " COMMAND_NAME");
	else if (token == T_COMMENT)
		ft_fprintf(2, " COMMAND_COMMENT");
}

static void	print_token_value(char *arg, char token)
{
	char stop_char;

	if (token == T_NAME || token == T_COMMENT)
	{
		ft_fprintf(2, " \"%s\"\n", token == T_NAME ? NAME_CMD_STRING : \
		COMMENT_CMD_STRING);
		return ;
	}
	if (token == T_LABEL)
		stop_char = LABEL_CHAR;
	else
		stop_char = SEPARATOR_CHAR;
	ft_fprintf(2, " \"");
	while (*arg && *arg != stop_char && !ft_isspace(*arg))
	{
		ft_putchar_fd(*arg, 2);
		++arg;
	}
	ft_fprintf(2, "\"\n");
}

void		error_manager(t_champ **champ, char *error_address, char token)
{
	char	*token_value;

	if (!token)
		token = get_token_type(error_address);
	if (token)
	{
		ft_fprintf(2, "Syntax error at token [TOKEN]");
		print_error_position((*champ)->data, error_address);
		print_token(token);
		if (token != T_ENDLINE)
			print_token_value(error_address, token);
	}
	else
	{
		ft_fprintf(2, "Lexical error at ");
		print_error_position((*champ)->data, error_address);
		ft_fprintf(2, "\n");
	}
	free_champ(champ);
	exit(token);
}

void		invalid_parameter(t_champ **champ, char *data,\
			t_instr *instruction, int param)
{
	ft_fprintf(2, "Invalid parameter %d type", param);
	print_token(get_token_type(data));
	ft_fprintf(2, " for instruction %s\n", g_op_tab[instruction->code].name);
	del_one_instr(&instruction);
	free_champ(champ);
	exit(T_PARAMETER);
}
