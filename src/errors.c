/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:02:47 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/15 21:04:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexical_error(t_champ **champ, char *data, char *error_address)
{
	ft_fprintf(2, "Lexical error at ");
//	print_error_position(data, error_address);
	ft_fprintf(2, "\n");
	free_champ(champ);
	free(data);
	exit(LEXICAL_ERROR);
}

void		ft_exit(t_champ **champ, int err)
{
	if (err == USAGE)
		ft_fprintf(2, "Usage: ./asm <file name> (*.s)\n");
	else if (err == INVALID_FILE_NAME)
		ft_fprintf(2, "Error: Invalid input file\n");
	else if (err  == MALLOC_FAILURE)
		ft_fprintf(2, "Error: Failed to alloc memory\n");
	else
		perror("Error");
	free_champ(champ);
	exit(err);
}

static int	get_token_type(char *arg, t_op *op_tab)
{
	int i;

	i = skip_spaces(arg, 0);
	if (arg[i] == DIRECT_CHAR)
		return(T_DIR);
	if (arg[i] == REG_CHAR)
		return (T_REG);
	if (ft_isdigit(arg[i]))
		return(T_IND);
	if (arg[i] == '\n')
		return(T_ENDLINE);
	if (arg[i] == SEPARATOR_CHAR)
		return (T_SEPARATOR);
	if (get_instruct_code(arg, op_tab))
		return (T_INSTRUCTION);
	if (islabel(arg))
		return (T_LABEL);
	return(0);
}

static void	print_error_position(char *data, char *error_address)
{
	int		i;
	int		row;
	int		pos_in_row;

	i = 0;
	row = 1;
	pos_in_row = 1;
	while (&data[i] != error_address)
	{
		if (data[i] == '\n')
		{
			row++;
			pos_in_row = 0;
		}
		i++;
		pos_in_row++;
	}
	ft_fprintf(2, "[%03d:%03d]", row, pos_in_row);
}

static void	print_token(char token)
{
	if (token == T_DIR)
		ft_fprintf(2, " DIRECT", 1);
	else if (token == T_IND)
		ft_fprintf(2, " INDIRECT", 2);
	else if (token == T_REG)
		ft_fprintf(2, " REGISTER", 2);
	else if (token == T_ENDLINE)
		ft_fprintf(2, " ENDLINE\n");
	else if (token == T_SEPARATOR)
		ft_fprintf(2, " SEPARATOR\n");
	else if (token == T_INSTRUCTION)
		ft_fprintf(2, " INSTRUCTION\n");
	else if (token == T_LABEL)
		ft_fprintf(2, " LABEL\n");
}

static void print_token_value(char *arg, char token)
{
	if (token == T_DIR || token == T_REG || token == T_IND)
	{
		ft_fprintf(2, " \"");
		while (*arg && *arg != SEPARATOR_CHAR && !ft_isspace(*arg))
		{
			ft_putchar_fd(*arg, 2);
			++arg;
		}
		ft_fprintf(2, "\"\n");
	}
}

void	error_manager(t_champ **champ, char *data, char *error_address)
{
	char	token;
	char	*token_value;

	token = get_token_type(error_address, (*champ)->op_tab);
	if (token)
	{
		ft_fprintf(2, "Syntax error at token [TOKEN]");
		print_error_position(data, error_address);
		print_token(token);
		print_token_value(error_address, token);
	}
	else
	{
		ft_fprintf(2, "Lexical error at ");
		print_error_position(data, error_address);
		ft_fprintf(2, "\n");
	}
	free_champ(champ);
	free(data);
	exit(token);
}


