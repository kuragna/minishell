/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:55:52 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/20 17:23:20 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/ms_lexer.h"
#include "../include/minishell.h"

extern char	*words[];

t_lexer	ms_lexer_init(char *line)
{
	t_lexer	lexer;

	lexer.pos = 0;
	lexer.line = line;
	lexer.len = ft_strlen(line);
	return (lexer);
}

int	ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return (l->pos);
}
int	ms_is_token(int c)
{
	return (ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == '&');
}

t_token_type	ms_peek(t_lexer *l)
{
	const char		*tokens = "|<>";
	const size_t	len = ft_strlen(tokens);
	size_t			i;

	i = 0;
	l->pos = ms_trim_left(l);
	if (l->pos >= l->len)
		return (NEWLINE);
	if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<')
		return (DLESS);
	if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '>')
		return (DGREAT);
	if (l->line[l->pos] == '|' && l->line[l->pos + 1] == '|')
		return (OR);
	if (l->line[l->pos] == '&' && l->line[l->pos + 1] == '&')
		return (AND);
	while (i < len)
	{
		if (l->line[l->pos] == tokens[i])
			return (i + PIPE);
		i += 1;
	}
	return (WORD);
}

t_token	ms_token_next(t_lexer *l)
{
	char			c;
	t_token			token;

	l->pos = ms_trim_left(l);
	ft_memset(&token, 0, sizeof(token));
	if (l->pos >= l->len)
		return (token);
	c = l->line[l->pos];
	if (ms_is_token(c))
	{
		l->pos += 1;
		if (c == l->line[l->pos] && ms_is_token(l->line[l->pos]))
		{
			l->pos += 1;
		}
		return (token);
	}
	token.type = WORD;
	token.lexeme = ms_get_lexeme(l);
	return (token);
}


