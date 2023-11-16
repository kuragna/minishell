/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_final.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/11/14 20:29:23 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# define SINGLE '\''
# define DOUBLE '\"'


void ft_leaks()
{
	system("leaks -q minishell");
}
struct s_lex
{
	char	*line;
	size_t	len;
	size_t	start;
	size_t	pos;
	char	*content;
};


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
	printf("string = %s\n", string);
	if (ft_strchr(string, '\'') || ft_strchr(string, '\"'))
	{
		while (i < len_string && string[i] != '\0')
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
		printf("final string = %s\n", new_content);
		return (new_content);
	}
	return (string);
}


//INTERESTING = if you free string, you also free the nodes of the list
//DONE: add check for when SINGLE_QUOTE OR DOUBLE_QUOTE aren't closed
//DONE: lex->pos of string when in normal mode doesn't get tokenized => make this cleaner
//TODO: add conditions for when delimiter is found in line
char *single_quote_mode_new(struct s_lex *lex)
{
	size_t	quote_pos;

	quote_pos = lex->pos;
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != SINGLE_QUOTE)
		lex->pos++;
	if (quote_pos + 1 == lex->pos)
	{
		lex->pos++;
		return NULL;
	}
	while (lex->line[lex->pos] && lex->line[lex->pos] != SPACE)
		lex->pos++;
	lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	lex->content = ft_clean_string(lex->content);
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;
	return (lex->content);
}

char *double_quote_mode_new(struct s_lex *lex)
{
	size_t 	quote_pos;
	
	quote_pos = lex->pos;
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != DOUBLE_QUOTE)
		lex->pos++;
	if (quote_pos + 1 == lex->pos)
	{
		lex->pos++;
		return NULL;
	}
	while (lex->line[lex->pos] && lex->line[lex->pos] != SPACE)
		lex->pos++;
	lex->content = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	lex->content = ft_clean_string(lex->content);
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;
	return (lex->content);
}

int	is_token(int c)
{
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
char	*quote(struct s_lex *lex)
{
	char	*str;

	str = NULL;

	if (!check_quotes(lex->line))
		return (ft_putstr_fd("Quotes are not enclosed\n", 2), NULL);
	while (lex->pos < lex->len && lex->line[lex->pos] != DOUBLE_QUOTE)
		lex->pos++;
	lex->pos++;
	while (lex->pos < lex->len && lex->line[lex->pos] != DOUBLE_QUOTE)
		lex->pos++;
	/* if (lex->pos < lex->len && lex->line[lex->pos] == DOUBLE_QUOTE)
		str = quote(lex); */
	printf("lex->line char at pos %ld = [%c]\n", lex->pos, lex->line[lex->pos]);
	/* if (quote_pos + 1 == lex->pos)
		return NULL; */
	while (lex->pos < lex->len && !is_token(lex->line[lex->pos]))
		lex->pos++;
	str = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	str = ft_clean_string(str);
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;
	return (str);
}

int main()
{
	/*atexit(ft_leaks);*/
	struct s_lex lex;
	while (1)
	{
		ft_memset(&lex, 0, sizeof(lex));
		lex.line = readline("$> ");
		if (!lex.line)
			break ;
		lex.len = ft_strlen(lex.line);
		lex.pos = 0;
		lex.start = 0;
		printf("RE: [%s]\n", quote(&lex));
		printf("MAIN: pos = %ld\n", lex.pos);
		printf("MAIN: start = %ld\n", lex.start);
		//ms_exit(lex.line);
		add_history(lex.line);
	}
	return (0);
}
