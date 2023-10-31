#include "../include/minishell.h"

int ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return l->pos;
}
