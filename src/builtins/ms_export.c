#include "../../include/minishell.h"

// TODO: extract VALUE from single quotes and double quotes

static int	ms_export_(t_env *env, char *var)
{
	char	*end;
	int		i;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
	{
		return ms_error("export: `%s\': not a valid identifier\n", var);
	}
	end = ft_strchr(var, '=');

	len = end - var;
	
	i = ms_get_idx(env, var, len);

	var = ft_strdup(var);
	if (i != -1)
	{
		free(env->vars[i]);
		env->vars[i] = var;
		return (0);
	}
	env_add(env, var);
	return (0);
	
}

static void	ms_export_print(t_env *env)
{
	size_t	i;

	i = 0;
	env_sort(env);
	while (i < env->length)
	{
		if (env->vars[i][0])
			printf("declare -x %s\n", env->vars[i]);
		i += 1;
	}
}


int	ms_export(t_env *env, char **vars)
{
	size_t i;

	i = 0;
	if (*vars == NULL)
		ms_export_print(env);
	while (vars[i])
	{
		ms_export_(env, vars[i]);
		i += 1;
	}
	return (0);
}