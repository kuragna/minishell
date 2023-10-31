#include "../include/minishell.h"

int	ms_ismetachar(int c)
{
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
