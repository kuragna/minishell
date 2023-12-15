/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:34:39 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/13 13:33:11 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"
#include <stdio.h>

static char	*ms_rewording(const char *str, int quote)
{
	size_t			i;
	int				flag;
	struct s_string	re;

	i = -1;
	flag = 0;
	if (!str)
		return (NULL);
	re = ms_string_init();
	while (re.data && str[++i])
	{
		if (str[i] == quote)
			quote += 5;
		if (ms_isspecial(str[i]))
		{
			flag = 1;
			ms_char_append(&re, quote);
		}
		ms_char_append(&re, str[i]);
		if (flag)
			ms_char_append(&re, quote);
		flag = 0;
	}
	ms_char_append(&re, '\0');
	return (re.data);
}

static void	ms_expansion(t_lexer *l, struct s_string *word)
{
	char			c;
	char			*str;
	struct s_string	dollar;

	l->pos += 1;
	dollar = ms_string_init();
	while (dollar.data && l->pos < l->len)
	{
		ms_expand_exit_status(l, word);
		if (ms_is_token(l->line[l->pos]) || !ms_is_usalnum(l->line[l->pos]))
			break ;
		c = l->line[l->pos];
		ms_char_append(&dollar, c);
		l->pos += 1;
		if (l->line[l->pos] == '$' || !ms_is_usalnum(l->line[l->pos]))
		{
			ms_char_append(&dollar, '\0');
			str = ms_getenv(l->data.env, dollar.data);
			ms_str_append(word, ms_rewording(str, 34));
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
		if (c == '\"' && l->line[l->pos] == '$')
		{
			ms_expansion(l, word);
			if (l->line[l->pos] == '$' && l->line[l->pos + 1])
				continue ;
		}
		if (l->line[l->pos] != c)
		{
			ms_char_append(word, l->line[l->pos]);
			l->pos += 1;
		}
	}
	l->pos += 1;
}

static void	ms_tilde(t_lexer *l, struct s_string *word)
{
	const char	c = l->line[l->pos + 1];
	char		*home;

	if (!(ms_is_token(c) || c == '/' || c == '\0'))
		return ;
	home = ms_getenv(l->data.env, "HOME");
	l->pos += 1;
	ms_str_append(word, home);
}

char	*ms_get_lexeme(t_lexer *l)
{
	struct s_string	word;

	word = ms_string_init();
	if (!word.data)
		return (NULL);
	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		l->pos = ms_trim_left(l);
		if (l->line[l->pos] == '~')
			ms_tilde(l, &word);
 		if (l->line[l->pos] == '$')
		{
			ms_expansion(l, &word);
			ms_str_append(&word, &l->line[l->pos]);
			ms_char_append(&word, '\0');
			free(l->line);
			l->pos = 0;
			l->line = word.data;
			l->len = ft_strlen(l->line);
			return (ms_token_next(l));
		}
		ms_lexeme_(l, &word);
	}
	ms_char_append(&word, '\0');
	return (word.data);
}
