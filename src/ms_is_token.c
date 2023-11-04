#include "../include/minishell.h"

int	ms_is_token(int c)
{
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
