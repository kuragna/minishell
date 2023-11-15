#include "../include/minishell.h"

// TODO: ?
char	**ms_envcpy(t_array *env)
{
	size_t	i;
	char	**e;
	
	i = 0;
	e = malloc(sizeof(e) * (env->len + 1));
	if (!e)
		return (NULL);
	while (i < env->len)
	{
		if (ft_strchr(env->items[i], '='))
			e[i] = env->items[i];
		i += 1;
	}
	e[i] = NULL;
	return (e);
}
