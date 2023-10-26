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

int	ms_get_idx(t_env *env, const char *var, size_t len)
{
	size_t i;

	i = 0;
	while (i < env->length)
	{
		if (ft_strncmp(env->vars[i], var, len) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}