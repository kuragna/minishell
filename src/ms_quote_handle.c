/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:34:39 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/21 20:10:20 by aabourri         ###   ########.fr       */
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

static	int	ms_is_usalnum(int c)
{
	return (ft_isalnum(c) || c == '_');
}

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
static int	ms_char_append(struct s_string *str, const char c)
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

static void	ms_str_append(struct s_string *str, const char *s)
{
	while (s && *s)
	{
		ms_char_append(str, *s);
		s += 1;
	}
}


static void	ms_dollar(t_lexer *l, struct s_string *word)
{
	char			c;
	char			*str;
	struct s_string dollar;

	dollar = ms_string_init();
	l->pos += 1;
	while (l->pos < l->len)
	{
		if (ms_is_token(l->line[l->pos]) || !ms_is_usalnum(l->line[l->pos]))
			break ;
		c = l->line[l->pos];
		ms_char_append(&dollar, c);
		l->pos += 1;
		if (l->line[l->pos] == '$' || !ms_is_usalnum(l->line[l->pos]))
		{
			ms_char_append(&dollar, '\0');
			str = ms_getenv(l->env, dollar.data);
			printf("here\n");
			ms_str_append(word, str);
			dollar.len = 0;
			if (l->line[l->pos] == '$')
				l->pos += 1;
		}
	}
	printf("pos -> `%s`\n", &l->line[l->pos]);
}

static void	ms_quote_consume(t_lexer *l, struct s_string *word, char c)
{
	while (l->pos < l->len && l->line[l->pos] != c)
	{
		if (l->line[l->pos] == '$' && c == '\"')
		{
			ms_dollar(l, word);
		}
		else
		{
			ms_char_append(word, l->line[l->pos]);
			l->pos += 1;
		}
	}
	l->pos += 1;
}

// DONE: two dollars
// DONE: handle ~
// DONE: handle cd "~/"
// DONE: fix $ HOME
// TODO: make sure that command as variable executed
// TODO: change the condition in env
// TODO: change the name of this file
// TODO: handle "$""H""O""M""E"
// TODO: skip last quote -- example  ls "'$HOME'"
// TODO: tokens as string literal

void	ms_tilde(t_lexer *l, struct s_string *word)
{
	const char 	c = l->line[l->pos + 1];
	const char	*home = ms_getenv(l->env, "HOME");

	if (!(c == ' ' || c == '/' || c == '\0'))
		return ;
	l->pos += 1;
	if (ft_isspace(l->line[l->pos]))
		l->pos += 1;
	ms_str_append(word, home);
}
// TODO: fix $$USER

char	*ms_get_lexeme(t_lexer *l)
{
	struct s_string	word;
	char			quote;

	word = ms_string_init();
	if (!word.data)
		return (NULL);
	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		l->pos = ms_trim_left(l);
		if (l->line[l->pos] == '~')
		{
			ms_tilde(l, &word);
		}
		if (l->line[l->pos] == '$' && ms_start(l->line[l->pos + 1]))
		{
			printf("we are here %s\n", &l->line[l->pos]);
			ms_dollar(l, &word);
		}
		else if (ms_is_quote(l->line[l->pos]))
		{
			quote = l->line[l->pos];
			l->pos += 1;
			ms_quote_consume(l, &word, quote);
		}
		while (l->pos < l->len)
		{
			if (ms_is_quote(l->line[l->pos]) || ms_is_token(l->line[l->pos]))
			{
				break ;
			}
			if (l->line[l->pos] == '$' && ft_isdigit(l->line[l->pos + 1]))
				l->pos += 2;
			ms_char_append(&word, l->line[l->pos]);
			l->pos += 1;
			if (l->line[l->pos] == '$')
				break ;
		}
	}
	ms_char_append(&word, '\0');
	return (word.data);
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
