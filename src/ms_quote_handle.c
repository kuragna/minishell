/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:34:39 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/20 20:05:34 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"
#include <stdio.h>

struct s_string
{
	char	*data;
	size_t	cap;
	size_t	len;
};

static int	ms_is_quote(int c)
{
	return (c == '\"' || c == '\'');
}

struct s_string ms_string_init()
{
	struct s_string string;

	string.cap = 8;
	string.len = 0;
	string.data = malloc(sizeof(*string.data) * string.cap);
	return (string);
}

// TODO: check NULL for str->data
static int	ms_str_append(struct s_string *str, char c)
{
	if (str->cap == str->len)
	{
		str->cap *= 2;
		str->data = ft_realloc(str->data, sizeof(*str->data) * str->cap);
		if (!str->data)
			return (1);
	}
	str->data[str->len] = c;
	str->len += 1;
	return (0);
}

static void	ms_dollar(t_lexer *l, struct s_string *string)
{
	char	c;
	char	*str;
	struct s_string dollar;

	dollar = ms_string_init();
	l->pos += 1;
	while (l->pos < l->len)
	{
		c = l->line[l->pos];
		if (!(ft_isalnum(c) || c == '_'))
			break ;
		ms_str_append(&dollar, l->line[l->pos]);
		l->pos += 1;
	}
	ms_str_append(&dollar, '\0');
	str = ms_getenv(l->env, dollar.data);
	while (str && *str)
	{
		ms_str_append(string, *str);
		str += 1;
	}
}

static void	ms_quote_consume(t_lexer *l, struct s_string *str, char c)
{

	while (l->pos < l->len && l->line[l->pos] != c)
	{
		if (l->line[l->pos] == '$' && c == '\"')
		{
			ms_dollar(l, str);
		}
		else
		{
			ms_str_append(str, l->line[l->pos]);
			l->pos += 1;
		}
	}
	l->pos += 1;
}

// TODO: two dollars
// TODO: change the name of this file

char	*ms_get_lexeme(t_lexer *l)
{
	struct s_string	string;
	char			quote;

	string = ms_string_init();
	if (!string.data)
		return (NULL);
	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		if (l->line[l->pos] == '$')
		{
			ms_dollar(l, &string);
		}
		else if (!ms_is_quote(l->line[l->pos]))
		{
			ms_str_append(&string, l->line[l->pos]);
			l->pos += 1;
		}
		else
		{
			quote = l->line[l->pos];
			l->pos += 1;
			ms_quote_consume(l, &string, quote);
		}
	}
	ms_str_append(&string, '\0');
	return (string.data);
}

int	ms_check_quotes(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (ms_is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
			{
				ms_error("minishell: unclosed quote: %s\n", &quote);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
