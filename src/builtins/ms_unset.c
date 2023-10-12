#include "../../include/minishell.h"

int	ms_unset(t_env *env, char *name)
{
	size_t	i;
	size_t	len;

	if (!ms_start(*name) || !ms_symbol(name, 0))
	{
		MS_ERROR("unset: ", name, ": not a valid identifier");
		return (1);
	}
	i = 0;
	len = ft_strlen(name);
	while (i < env->lenght && env->vars[i])
	{
		if (ft_strncmp(env->vars[i], name, len) == 0)
		{
			env->vars[i] = "";
			break ;
		}
		i += 1;
	}
	return (0);
}