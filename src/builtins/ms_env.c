//#include "../../include/minishell.h"

#include "../../include/ms_builtin.h"
/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * 
 * */

t_env ms_env_dup(char **envp)
{
	size_t	i;
	char	*str;
	t_env	env;

	i = 0;
	env.length = 0;
	env.capacity = 16;
	env.vars = malloc(sizeof(env.vars) * env.capacity);
	while (envp[i] != NULL)
	{
		str = ft_strdup(envp[i]);
		if (str)
			ms_env_push(&env, str);
		i += 1;
	}
	return env;
}


void	ms_swap(char **a, char **b)
{
	char *c = *a;
	*a = *b;
	*b = c;
}

int	ms_env_push(t_env *env, char *var)
{
	if (env->capacity == env->length)
	{
		env->capacity *= 2;
		env->vars = ft_realloc(env->vars, sizeof(env->vars) * env->capacity);
		if (!env->vars)
			return (1);
	}
	env->vars[env->length] = var;
	env->length += 1;
	return (0);
}

void	ms_env_sort(t_env env)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (i < env.length)
	{
		j = 0;
		len = ft_strlen(env.vars[i]);
		while (j < env.length)
		{
			if (ft_strncmp(env.vars[i], env.vars[j], len) < 0)
			{
				t = env.vars[i];
				env.vars[i] = env.vars[j];
				env.vars[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
}

int	ms_env(t_env env)
{
	size_t	i;

	i = 0;
	while (env.vars[i] != NULL)
	{
		ft_printf("%s\n", env.vars[i]);
		i += 1;
	}
	return (0);
}