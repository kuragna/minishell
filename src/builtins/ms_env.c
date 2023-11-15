//#include "../../include/minishell.h"

#include "../../include/ms_builtin.h"

/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * 
 * */

t_array ms_env_dup(char **envp)
{
	t_array array;
	size_t	i;
	char	*str;

	i = 0;
	array = ms_array_init();
	while (envp[i] != NULL)
	{
		str = ft_strdup(envp[i]);
		if (str)
			ms_array_append(&array, str);
		i += 1;
	}
	return (array);
}


void	ms_swap(char **a, char **b)
{
	char *c = *a;
	*a = *b;
	*b = c;
}

// int	ms_env_push(t_env *env, char *var)
// {
// 	if (env->capacity == env->length)
// 	{
// 		env->capacity *= 2;
// 		env->vars = ft_realloc(env->vars, sizeof(env->vars) * env->capacity);
// 		if (!env->vars)
// 			return (1);
// 	}
// 	env->vars[env->length] = var;
// 	env->length += 1;
// 	return (0);
// }

void	ms_env_sort(t_array env)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (i < env.len)
	{
		j = 0;
		len = ft_strlen(env.items[i]);
		while (j < env.len)
		{
			if (ft_strncmp(env.items[i], env.items[j], len) < 0)
			{
				t = env.items[i];
				env.items[i] = env.items[j];
				env.items[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
}

int	ms_env(t_array env)
{
	size_t	i;

	i = 0;
	while (env.items[i] != NULL)
	{
		ft_printf("%s\n", env.items[i]);
		i += 1;
	}
	return (0);
}