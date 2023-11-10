#include "../include/minishell.h"

int ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return l->pos;
}

int	ms_is_token(int c)
{
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
