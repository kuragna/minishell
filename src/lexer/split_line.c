/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/26 16:44:50 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# define SINGLE '\''
# define DOUBLE '\"'

int check_quotes(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == SINGLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != SINGLE_QUOTE)
				i++;
			if (str[i] != SINGLE_QUOTE)
				return (0);
			i++;
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != DOUBLE_QUOTE)
				i++;
			if (str[i] != DOUBLE_QUOTE)
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

int ft_isprint_no_quotes_spaces(char c)
{
	return (c > 32 && c < 127 && c != SINGLE_QUOTE && c != DOUBLE_QUOTE);
}

int ft_isprint_no_quotes(char c)
{
	return (c > 31 && c < 127 && c != SINGLE_QUOTE && c != DOUBLE_QUOTE);
}

char *ft_clean_string(char *string)
{
	char *new_content;
	size_t	i;
	size_t	j;
	size_t len_string;


	i = 0;
	j = 0;
	len_string = ft_strlen(string);
	new_content = malloc(sizeof(char) * len_string + 1);
	if (!new_content)
		return NULL;
	if (ft_strchr(string, '\'') || ft_strchr(string, '\"'))
	{
		while (string[i] && string[i] != '\0')
		{
			if (string[i] == SINGLE_QUOTE)
			{
				i++;
				while (string[i] && string[i] != SINGLE_QUOTE)
					new_content[j++] = string[i++];
				i++;
			}
			else if (string[i] == DOUBLE_QUOTE)
			{
				i++;
				while (string[i] && string[i] != DOUBLE_QUOTE)
					new_content[j++] = string[i++];
				i++;
			}
			else
				new_content[j++] = string[i++];
		}
		new_content[j] = '\0';
		return (new_content);
	}
	return (string);
}


//INTERESTING = if you free string, you also free the nodes of the list
//DONE: add check for when SINGLE_QUOTE OR DOUBLE_QUOTE aren't closed
//DONE: lex->pos of string when in normal mode doesn't get tokenized => make this cleaner
//TODO: add conditions for when delimiter is found in line
void single_quote_mode(t_token *token, t_lexer *lex)
{
	size_t	quote_pos;

	quote_pos = lex->pos;
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != SINGLE_QUOTE)
		lex->pos++;
	if (quote_pos + 1 == lex->pos)
		return;
	while (lex->line[lex->pos] && lex->line[lex->pos] != SPACE)
		lex->pos++;
	lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	lex->content = ft_clean_string(lex->content);
	ft_lstadd_back(&token->list, ft_lstnew(lex->content));
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;
}

void double_quote_mode(t_token *token, t_lexer *lex)
{
	size_t 	quote_pos;
	
	quote_pos = lex->pos;
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != DOUBLE_QUOTE)
		lex->pos++;
	if (quote_pos + 1 == lex->pos)
		return;
	while (lex->line[lex->pos] && lex->line[lex->pos] != SPACE)
		lex->pos++;
	lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	lex->content = ft_clean_string(lex->content);
	ft_lstadd_back(&token->list, ft_lstnew(lex->content));
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;

}


char *create_metachar_string(char *line)
{
	size_t i;
	char *temp;
	int flag;

	flag = 0;
	i = 0;
	if (line[i+1] && line[i] == line[i + 1] && (line[i+1] == '>' || line[i+1] == '<'))
	{
		temp = malloc(3);
		flag = 1;
	}
	else
		temp = malloc(2);
	if (flag == 1)
	{
		temp[0] = line[0];
		temp[1] = line[1];
		temp[2] = '\0';
	}
	else
	{
		temp[0] = line[0];
		temp[1] = '\0';
	}
	return (temp);
}

//TODO: shell never exists, should just print the error and give back the prompt
t_token *split_line(t_lexer *lex)
{
	t_token	*token;
	token = NULL;
	
	token = malloc(sizeof(t_token));
	ft_memset(token, 0, sizeof(*token));
	lex->len = ft_strlen(lex->line);
	if (!check_quotes(lex->line))
		return (ft_putstr_fd("Quotes are not enclosed\n", 2), NULL);
	while (lex->pos <= lex->len)
	{
		while (ft_isspace(lex->line[lex->start]))
			lex->start++;
		if (lex->line[lex->pos] && lex->line[lex->pos] == SINGLE_QUOTE)
			single_quote_mode(token, lex);
		else if (lex->line[lex->pos] == DOUBLE_QUOTE)
			 double_quote_mode(token, lex);
		else if (ms_is_metachar(lex->line[lex->pos]) == 1)
		{
			if (lex->pos - lex->start > 0)
			{
				lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
				lex->content = ft_strtrim(lex->content, " ");
				lex->content = ft_clean_string(lex->content);
				ft_lstadd_back(&token->list, ft_lstnew(lex->content));
			}
			lex->temp = create_metachar_string(lex->line + lex->pos);
			if (ft_strlen(lex->temp) > 1)
				lex->pos++;
			ft_lstadd_back(&token->list, ft_lstnew(lex->temp));
			if (lex->line[lex->pos] != '\0')
				lex->start = lex->pos + 1;
		}
		else if (lex->pos == lex->len)
		{
			lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
			lex->content = ft_clean_string(lex->content);
			if (ft_strlen(lex->content) == 0)	
				return (token);
			ft_lstadd_back(&token->list, ft_lstnew(lex->content));
		}
		lex->pos++;
	}
	return (token);
}


void ft_leaks()
{
	system("leaks -q minishell");
}
#if 0 

int main()
{
	/*atexit(ft_leaks);*/
	t_lexer	lex;
	t_token *token;
	while (1)
	{
		ft_memset(&lex, 0, sizeof(lex));
		lex.line = readline("$> ");
		ms_exit(lex.line);
		add_history(lex.line);
		token = split_line(&lex);
		while (token && token->list != NULL)
		{
			printf("\ncontent = [%s]\n", (char *)token->list->content);
			token->list = token->list->next;
		}
	}
	return (0);
}

#endif
