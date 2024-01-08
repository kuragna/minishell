/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:29:43 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/27 16:31:53 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"

extern int	g_status;

static void	ms_heredoc_quote(t_lexer *l, struct s_string *word, char quote)
{
	while (l->pos < l->len && l->line[l->pos] != quote)
	{
		ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
	}
	l->pos += 1;
}

char	*ms_heredoc_dlmtr(t_lexer *l, struct s_string *word)
{
	char	quote;

	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		if (ms_is_quote(l->line[l->pos]))
		{
			l->data.quotes_flag = 1;
			quote = l->line[l->pos];
			l->pos += 1;
			ms_heredoc_quote(l, word, quote);
		}
		if (l->pos >= l->len)
			break ;
		if (!ms_is_token(l->line[l->pos]))
			ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
	}
	ms_char_append(word, '\0');
	return (word->data);
}

static void	ms_heredoc_exit_status(struct s_string *word)
{
	char	*status;

	status = ft_itoa(g_status);
	if (status)
	{
		ms_str_append(word, status);
		free(status);
	}
}

// TODO: divide this two parts
char	*ms_heredoc_expansion(const char *name, t_data *data)
{
	char			*str;
	struct s_string	word;
	struct s_string	dollar;

	word = ms_string_init();
	dollar = ms_string_init();
	while (name && *name)
	{
		if (*name == '$' && *(name + 1))
		{
			name += 1;
			if (*name == '?')
			{
				ms_heredoc_exit_status(&word);
				name += 1;
			}
			while (*name && *name != '$' && ms_is_usalnum(*name))
			{
				ms_char_append(&dollar, *name);
				name += 1;
			}
			ms_char_append(&dollar, '\0');
			str = ms_getenv(data->env, dollar.data);
			ms_str_append(&word, str);
			dollar.len = 0;
		}
		if (*name)
		{
			ms_char_append(&word, *name);
			name += 1;
		}
	}
	free(dollar.data);
	return (ms_char_append(&word, '\0'), word.data);
}
