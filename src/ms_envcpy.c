#include "../include/minishell.h"

// TODO: ?
char	**ms_envcpy(const t_env *env)
{
	size_t	i;
	char	**e;
	
	i = 0;
	e = malloc(sizeof(e) * (env->length + 1));
	if (!e)
		return (NULL);
	while (i < env->length)
	{
		if (ft_strchr(env->vars[i], '='))
			e[i] = env->vars[i];
		i += 1;
	}
	e[i] = NULL;
	return (e);
}
