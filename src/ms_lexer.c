#include "../include/ms_lexer.h"
#include "../libft/libft.h" // For substr

t_lexer ms_lexer_init(char *line)
{
	t_lexer	lexer;

	lexer.pos = 0;
	lexer.line = line;
	lexer.len = ft_strlen(line);
	return lexer;
}
t_token_type ms_peek(t_lexer *l)
{
	const char *tokens = "|<>$\'\"";
	const size_t len = ft_strlen(tokens);
	size_t i;

	i = 0;
	l->pos = ms_trim_left(l);
	if (l->pos >= l->len)
		return (END);
	if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<')
		return (DLESS);
	if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '>')
		return (DGREAT);
	while (i < len)
	{
		if (l->line[l->pos] == tokens[i])
			return (i + PIPE);
		i += 1;
	}
	return (WORD);
}

t_token ms_token_next(t_lexer *l)
{
	size_t	i = 0;
    t_token token;
	const char *tokens = "|<>";
	const size_t	size = ft_strlen(tokens);

	ft_bzero(&token, sizeof(token));
    l->pos = ms_trim_left(l);
    if (l->pos > l->len) return token;
	while (i < size)
	{
		if (l->line[l->pos] == tokens[i])
		{
			i = 0;
			l->pos += 1;
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
	if (l->line[l->pos] == '\'' || l->line[l->pos] == '\"')
	{
		l->pos += 1;
		token.type = WORD; // TODO: change token type for expand it.
		token.len = ms_consume(l, ms_isquote);
		// TODO: just safe start and end, allocate memory later.
		token.lexeme = ft_substr(&l->line[l->pos], 0, token.len);
		l->pos += token.len + 1;
		return token;
	}
    if (l->pos < l->len)
    {
		token.len = ms_consume(l, ms_is_token);
        token.type = WORD;
        token.lexeme = ft_substr(&l->line[l->pos], 0, token.len);
        l->pos += token.len;
    }
    return token;
}

int	ms_isquote(int c)
{
	return c == '\'' || c == '\"';
}

int	ms_consume(t_lexer *l, int (*check)(int))
{
	size_t start = l->pos;
	size_t len = 0;

	while (start < l->len && !check(l->line[start]))
	{
		start += 1;
		len += 1;
	}
	return len;
}