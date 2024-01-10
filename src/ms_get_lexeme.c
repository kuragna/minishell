/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_lexeme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:34:39 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/10 13:31:35 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"

#define MS_AMB "ambiguous redirect"

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
		if (ms_is_special(str[i]))
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

int	ms_expansion(t_lexer *l, struct s_string *word)
{
	char			*str;
	struct s_string	dollar;

	l->pos += 1;
	dollar = ms_string_init();
	while (dollar.data && l->pos < l->len)
	{
		ms_expand_exit_status(l, word);
		if (ms_is_token(l->line[l->pos]) || !ms_is_usalnum(l->line[l->pos]))
			break ;
		ms_char_append(&dollar, l->line[l->pos]);
		l->pos += 1;
		if (l->line[l->pos] == '$' || !ms_is_usalnum(l->line[l->pos]))
		{
			ms_char_append(&dollar, '\0');
			str = ms_getenv(l->data.env, dollar.data);
			if (l->prev >= LESS && l->prev <= DGREAT && ft_strchr(str, ' '))
				return (ms_error("minishell: $%s: %s\n", dollar.data, MS_AMB));
			ms_str_append(word, ms_rewording(str, 34));
			dollar.len = 0;
			if (l->line[l->pos] == '$')
				l->pos += 1;
		}
	}
	return (free(dollar.data), 1);
}

void	ms_quote_consume(t_lexer *l, struct s_string *word, char quote)
{
	char	ch;

	while (l->pos < l->len && l->line[l->pos] != quote)
	{
		ch = l->line[l->pos + 1];
		if (quote == '\"' && l->line[l->pos] == '$')
		{
			ms_expansion(l, word);
			if (l->line[l->pos] == '$' && l->line[l->pos + 1])
				continue ;
		}
		if (l->line[l->pos] != quote)
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
	int				flag;
	struct s_string	word;

	flag = 0;
	word = ms_string_init();
	while (word.data && (l->pos < l->len && !ms_is_token(l->line[l->pos])))
	{
		l->pos = ms_trim_left(l);
		if (l->prev == DLESS)
			return (ms_heredoc_dlmtr(l, &word));
		if (l->line[l->pos] == '~')
			ms_tilde(l, &word);
		if (l->line[l->pos] == '$')
		{
			if (ms_is_start(l->line[l->pos + 1]) || l->line[l->pos + 1] == '?')
			{
				ms_expansion(l, &word);
				flag = 1;
			}
		}
		ms_lexeme_(l, &word);
	}
	return (ms_lexeme_value(flag, &word, l));
}
