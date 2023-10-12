#include "../../include/minishell.h"

int	ms_export(t_env *env, char *var)
{
	char	*end;
	int		i;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
	{
		MS_ERROR("export: ", var, ": not a valid identifier");
		return (1);
	}
	end = ft_strchr(var, '=');
	i = env->lenght - 1;

	len = end - var;
	while (i >= 0)
	{
		if (ft_strncmp(env->vars[i], var, len) == 0)
		{
			env->vars[i] = var;
			return (0);
		}
		i -= 1;
	}
	env_add(&env, var);
	env_append_null(env);
	return (0);
}
void	export_print(t_env *env)
{
	size_t	i;

	i = 0;
	env_sort(env);
	while (env->vars[i])
	{
		if (env->vars[i][0])
			printf("declare -x %s\n", env->vars[i]);
		i += 1;
	}
}