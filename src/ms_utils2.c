/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:51 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/09 20:06:55 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_envcpy(t_array *env)
{
	size_t	i;
	t_array	e;

	i = 0;
	e = ms_array_init();
	if (!e.items)
		return (NULL);
	while (i < env->len)
	{
		if (env->items[i] && ft_strchr(env->items[i], '='))
			ms_array_append(&e, env->items[i]);
		i += 1;
	}
	ms_array_append(&e, NULL);
	return (e.items);
}

void	ms_lexeme_(t_lexer *l, struct s_string *word)
{
	char	c;
	char	quote;

	if (ms_is_quote(l->line[l->pos]))
	{
		quote = l->line[l->pos];
		l->pos += 1;
		ms_quote_consume(l, word, quote);
	}
	while (l->pos < l->len)
	{
		c = l->line[l->pos + 1];
		if (l->line[l->pos] == '$' && (ft_isalpha(c) || c == '_' || c == '?'))
			ms_expansion(l, word);
		if (l->pos >= l->len)
			break ;
		if (ms_is_quote(l->line[l->pos]) || ms_is_token(l->line[l->pos]))
			break ;
		ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
	}
}

char	*ms_lexeme_value(int flag, struct s_string *word, t_lexer *l)
{
	if (flag)
	{
		ms_str_append(word, &l->line[l->pos]);
		ms_char_append(word, '\0');
		ms_lexer_init(l, word->data);
		return (ms_token_next(l));
	}
	ms_char_append(word, '\0');
	return (word->data);
}

void	ms_table_add(struct s_fd_table *table, int fd)
{
	if (table->len == 9000)
		return ;
	if (fd > 2)
	{
		table->fds[table->len] = fd;
		table->len += 1;
	}
}

void	ms_close(struct s_fd_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->len)
	{
		close(table->fds[i]);
		i += 1;
	}
}
