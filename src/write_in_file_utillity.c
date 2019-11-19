/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_file_utillity.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:49:11 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/19 20:19:58 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			reverse_bits(int num, char full_bit)
{
	int		rev_num;
	int		i;

	i = 0;
	if (full_bit)
	{
		rev_num = (num & 0xFF) << 24;
		rev_num = rev_num | ((num >> 8) & 0xFF) << 16;
		rev_num = rev_num | ((num >> 16) & 0xFF) << 8;
		rev_num = rev_num | ((num >> 24) & 0xFF);
	}
	else
	{
		rev_num = (num & 0xFF) << 8;
		rev_num = rev_num | ((num & 0xFF00) >> 8);
	}
	return (rev_num);
}

t_header	*create_header(void)
{
	t_header *head;

	head = (t_header*)malloc(sizeof(t_header));
	if (!head)
		return (NULL);
	ft_bzero((void*)head, sizeof(t_header));
	head->magic = reverse_bits(COREWAR_EXEC_MAGIC, 1);
	return (head);
}

int	copy2_head(t_champ *champ, t_header *head)
{
	ft_memcpy((void*)head->prog_name, (const void*)champ->name, ft_strlen(champ->name));
	ft_memcpy((void*)head->comment, (const void*)champ->comment, ft_strlen(champ->comment));
	head->prog_size = size_instr(champ->instr);
	return (0);
}

int	size_instr(t_instr *instr)
{
	int		size;

	while (instr->next)
		instr = instr->next;
	size = instr->offset + instr->instr_size;
	return (size);
}

int	define_code_args(t_instr *instr)
{
	char	code;
	int		i;
	int 	n;

	n = 6;
	i = 0;
	code = 0;
	while (i < 3)
	{
		if (instr->args[i].type == T_IND)
			code = code | (IND_CODE << n);
		else if(instr->args[i].type == T_REG)
			code = code | (REG_CODE << n);
		else if(instr->args[i].type == T_DIR)
			code = code | (DIR_CODE << n);
		n -= 2;
		++i;
	}
	return (code);	
}