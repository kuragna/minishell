#include "../../include/minishell.h"

#include <stdlib.h>


int	ms_start(int c)
{
	return ft_isalpha(c) || c == '_';
}

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

int	ms_get_idx(t_env *env, const char *var)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(var);
	while (i < env->length)
	{
		if (ft_strncmp(env->vars[i], var, len) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

char	*ms_getenv(t_env *env, char *name)
{
	char	*var;
	int		pos;

	if (env == NULL)
		return (NULL);
	pos = ms_get_idx(env, name);
	if (pos == -1)
		return (NULL);
	var =  ft_strchr(env->vars[pos], '=');
	if (var == NULL)
		return (NULL);
	return (var + 1);
}
