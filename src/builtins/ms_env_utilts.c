#include "../../include/minishell.h"

/* name of environment variable should start with underscore or alphabet*/
int	ms_start(int c)
{
	return ft_isalpha(c) || c == '_';
}
/* name of environment variable should not contain special characters,
	except underscore */
int	ms_symbol(char *str, int c)
{
	while (*str && *str != c)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);	
		str += 1;
	}
	return (1);
}