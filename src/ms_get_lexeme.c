/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:34:39 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/28 15:25:30 by aabourri         ###   ########.fr       */
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

static struct s_string ms_string_init()
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
	const size_t	size = sizeof(*str->data);

	if (str->cap == str->len)
	{
		str->cap *= 2;
		str->data = ft_realloc(str->data, str->len * size, size * str->cap);
// 		str->data = ft_realloc(str->data, sizeof(*str->data) * str->cap);
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



static void	ms_expansion(t_lexer *l, struct s_string *word)
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
			ms_str_append(word, str);
			dollar.len = 0;
			if (l->line[l->pos] == '$')
				l->pos += 1;
		}
	}
	free(dollar.data);
}

void	ms_quote_consume(t_lexer *l, struct s_string *word, char c)
{
	char	ch;

	while (l->pos < l->len && l->line[l->pos] != c)
	{
		ch = l->line[l->pos + 1];
		if (c == '\"' && l->line[l->pos] == '$' && ms_start(ch))
			ms_expansion(l, word);
		if (l->line[l->pos] != c)
		{
			ms_char_append(word, l->line[l->pos]);
			l->pos += 1;
		}
	}
	l->pos += 1;
}

// TODO: fix $blabla|$HOME
// TODO: handle $[non-usalpha][rest of characters]

void	ms_tilde(t_lexer *l, struct s_string *word)
{
	const char 	c = l->line[l->pos + 1];
	const char	*home = ms_getenv(l->env, "HOME");

	if (!(ms_is_token(c) || c == '/' || c == '\0'))
		return ;
	l->pos += 1;
	// TODO: we dont need it any more
// 	if (ft_isspace(l->line[l->pos]))
// 		l->pos += 1;
	ms_str_append(word, home);
}

int	ms_isspecial(int c)
{
	const int	a = ms_is_quote(c) || c == '~';

	return (a ||  c == '|' || c == '>' || c == '<' || c == '&');
}


char	*ms_rewording(struct s_string *word)
{
	char			quote;
	int				flag;
	struct s_string str;
	size_t			i;

	i = -1;
	flag = 0;
	str = ms_string_init();
	quote = 34;
	while (++i < word->len && word->data[i])
	{
		if (word->data[i] == quote)
			quote += 5;
		if (ms_isspecial(word->data[i]))
		{
			flag = 1;
			ms_char_append(&str, quote);
		}
		ms_char_append(&str, word->data[i]);
		if (flag)
			ms_char_append(&str, quote);
		flag = 0;
	}
	free(word->data);
	ms_char_append(&str, '\0');
	return str.data;
}

// int	main()
// {

// 	struct s_string word;

// 	word = ms_string_init();

// 	ms_str_append(&word, "|");


// 	char	*data = ms_rewordin






// 	return 0;
// }

#if 1
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
			ms_expansion(l, &word);
			ms_str_append(&word, &l->line[l->pos]);
			ms_char_append(&word, '\0');
			free(l->line);
			l->pos = 0;
			l->line = ms_rewording(&word);
			l->len = ft_strlen(l->line);
			return ms_token_next(l).lexeme;
		}
		else if (ms_is_quote(l->line[l->pos]))
		{
			quote = l->line[l->pos];
			l->pos += 1;
			ms_quote_consume(l, &word, quote);
			continue ;
		}
		while (l->pos < l->len)
		{
			if (ms_is_quote(l->line[l->pos]) || ms_is_token(l->line[l->pos]))
				break ;
			ms_char_append(&word, l->line[l->pos]);
			l->pos += 1;
			if (l->line[l->pos] == '$')
				break ;
		}
	}
	ms_char_append(&word, '\0');
	return (word.data);
}
#endif


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
			if (!str[i] || str[i] != quote)
			{
				ms_error("minishell: unclosed quote: %c\n", quote);
				return (1);
			}
		}
		i++;
	}
	return (0);
}