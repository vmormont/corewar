/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:45:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/12 19:32:54 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*static void		parse_name(t_champ *champ, char **filedata)
{
	char	**words;
	char	*tmp_word;
	int		i;

	i = -1;
	while (*filedata[++i] && (!champ->name || !champ->comment))
	{
		words = ft_strsplit((const char*)filedata[i], '"');
		tmp_word = ft_strtrim(words[0]);
		if (!ft_strcmp(tmp_word, NAME_CMD_STRING))
			champ->name = ft_strdup(words[1]);
		else if (!ft_strcmp(tmp_word, COMMENT_CMD_STRING))
			champ->comment = ft_strdup(words[1]);
		else
			break ;
		if (ft_strtrim((const char*)words[2])[0])
			lexical_error(&champ, NAME_ERROR, i, 33);
			//ft_printf ("THIRD ARGUMENT!!!!!!!!\n");
		//ft_printf("pointer = %p   ", ft_strtrim((const char*)words[2]));
		//ft_strtrim((const char*)words[2]) ? ft_printf("words = |%s\n", ft_strtrim((const char*)words[2])) : ft_printf("NULL\n");
	}
	if (!champ->name || !champ->comment)
		lexical_error(&champ, NAME_ERROR, i, 0);
}*/

//функция вычисляет номер строки и символа ошибки
//эту функцию нужно вставить в 
//lexical_error(t_champ *champ, char *data, char *error)
void        print_error_string(char *data, char *error)
{
    int string_num;
    int char_num;
    string_num = 0;
    char_num = 0;
    while (*data)
    {
        if (*data == '\n')
        {
            string_num++;
            char_num = 0;
        }
        if (data == error)
            break ;
        char_num++;
        data++;
    }
    ft_fprintf(2, "Error: lexical error at [%03d]:[%03d]\n",\
    string_num, char_num);
}

void        add_name_comment(t_champ *champ, char *data, int *i, char f)
{
    int     j;
    // пропускаем пробелы после ".name" или ".comment"
    while (ft_isspace(data[*i]))
        *i += 1;
    
    // если не начало строки сообщаем об ошибке
    if (data[(*i)++] != '"')
        lexical_error(&champ, data, &data[--*i]);
    
    //запонимаем индекс начала 
    j = *i;
    //проходим все предложение в " "
    while (data[*i] && data[*i] != '"')
        ++(*i);
    // в зависимости от флага добавляем имя или комментарий
    if (f)
        !(champ->name = ft_strsub(data, j, *i)) ?\
            ft_exit(&champ, MALLOC_FAILURE) : 0;
    else
		!(champ->comment = ft_strsub(data, j, *i)) ?\
            ft_exit(&champ, MALLOC_FAILURE) : 0;
    ++(*i);
	//переход на следущую строку 
    while (ft_isspace(data[*i]) && data[*i] != '\n')
        ++(*i);
    //если дошли до конца файла или не перешли на следующую строку
    //сообщаем об ошибке
    if (!data[*i] || data[*i] != '\n')
    {
		//ft_printf("data[%d] = %c\n", *i, data[*i]);
		lexical_error(&champ, data, &data[*i]);
	}
    ++(*i);
}

int         parse_name(t_champ *champ, char *data)
{
    int i;
    i = 0;
    //пропускаем все пробелы и пустые строки
    //т.к. комментарий может быть перед ".name" или ".comment"
    while (ft_isspace(data[i]))
        ++i;
    //добавляем имя и комментарий
    while(data[i] && (!champ->name || !champ->comment))
    {
        if(!ft_strncmp(&data[i], ".name", 5))
        {
            i += 5;
            add_name_comment(champ, data, &i, 1);
        }
        else if (!ft_strncmp(&data[i], ".comment", 8))
        {
            i += 8;
            add_name_comment(champ, data, &i, 0);
        }
        else
            lexical_error(&champ, data, &data[i]);
    }
    //возвращаем индекс последнего считанного символа
    return (i);
}


void		lexical_analizer(t_champ *champ, char *filedata)
{
	while (!champ->name || !champ->comment)
		parse_name(champ, filedata);
	ft_printf("%s\n%s\n", champ->name, champ->comment);
}

