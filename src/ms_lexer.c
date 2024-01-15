/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:55:52 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/15 12:29:46 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/ms_lexer.h"
#include "../include/minishell.h"

void	ms_lexer_init(t_lexer *l, const char *line)
{
	l->pos = 0;
	l->prev = 0;
	l->dollar_flag = 0;
	l->line = (char *)line;
	l->len = ft_strlen(line);
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
	return (ft_isspace(c) || c == '|' || c == '>' || c == '<');
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
	while (i < len && ms_is_token(l->line[l->pos]))
	{
		if (l->line[l->pos] == tokens[i])
			return (i + PIPE);
		i += 1;
	}
	return (WORD);
}

char	*ms_token_next(t_lexer *l)
{
	char	c;

	l->pos = ms_trim_left(l);
	if (l->pos >= l->len)
		return (NULL);
	c = l->line[l->pos];
	if (ms_is_token(c))
	{
		l->pos += 1;
		if (c == l->line[l->pos] && ms_is_token(l->line[l->pos]))
		{
			l->pos += 1;
		}
		return (NULL);
	}
	return (ms_get_lexeme(l));
}
