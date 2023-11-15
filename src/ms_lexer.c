#include "../include/ms_lexer.h"
#include "../libft/libft.h" // For substr
#include <stdio.h>

t_lexer ms_lexer_init(char *line)
{
	t_lexer	lexer;

	lexer.pos = 0;
	lexer.start = 0;
	lexer.line = line;
	lexer.len = ft_strlen(line);
	return lexer;
}
t_token_type ms_peek(t_lexer *l)
{
	const char 		*tokens = "|<>";
	const size_t 	len = ft_strlen(tokens);
	size_t			i;

	i = 0;
	l->pos = ms_trim_left(l);
	if (l->pos >= l->len)
		return (NEWLINE);
	if (ft_strchr(l->line, '\'') || ft_strchr(l->line, '\"'))
	{
		if (check_quotes(l->line))
			return (NEWLINE);
	}
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
		{
			return (i + PIPE);
		}
		i += 1;
	}
	return (WORD);
}

t_token ms_token_next(t_lexer *l)
{
	int	flag = 1;
	size_t	i = 0;
    t_token token;
	const char *tokens = "|<>&";
	const size_t	size = ft_strlen(tokens);

	ft_bzero(&token, sizeof(token));
    l->pos = ms_trim_left(l);
    if (l->pos >= l->len) return token;
	if (l->line[l->pos] == '|' && l->line[l->pos + 1] == '|')
	{
		l->pos += 2;
		return (token);
	}
	if (l->line[l->pos] == '&' && l->line[l->pos + 1] == '&')
	{
		l->pos += 2;
		return (token);
	}
	while (i < size)
	{
		if (l->line[l->pos] == tokens[i])
		{
			l->pos += 1;
			flag = 0;
			i = 0;
		}
		i += 1;
	}
	if (l->line[l->pos] == '$')
	{
		token.len = ms_consume(l, ms_is_token);
		token.type = DOLLAR;
		token.lexeme = ft_substr(&l->line[l->pos], 0, token.len);
		l->pos += token.len;
		return token;
	}
	if (ft_strchr(&l->line[l->pos], '\"'))
	{
		token.lexeme = quote(l, '\"');
		token.type = WORD;
		return token;
	}
	if (ft_strchr(&l->line[l->pos], '\''))
	{
		token.type = WORD;
		token.lexeme = quote(l, '\'');
		return token;
	}
    if (l->pos < l->len && flag)
    {
		token.len = ms_consume(l, ms_is_token);
        token.type = WORD;
        token.lexeme = ft_substr(&l->line[l->pos], 0, token.len);
        l->pos += token.len;
    }
    return token;
}

int	ms_is_quote(int c)
{
	return c == '\'' || c == '\"';
}

int	ms_consume(t_lexer *l, int (*check)(int))
{
	size_t	start;
	size_t	len;

	len = 0;
	start = l->pos;
	while (start < l->len && !check(l->line[start]))
	{
		start += 1;
		len += 1;
	}
	return len;
}