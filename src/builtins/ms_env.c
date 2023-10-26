#include "../../include/minishell.h"

/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * 
 * */

t_env env_dup(char **envp)
{
	size_t	i;
	t_env	env;

	i = 0;

	env.length = 0;
	env.capacity = env_size(envp);
	env.vars = malloc(sizeof(char *) * env.capacity); // check error

	while (envp[i] != NULL)
	{
		env.vars[i] = ft_strdup(envp[i]);
		i += 1;
	}
	env.length += i;
	return env;
}

size_t	env_size(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i += 1;
	}
	return i;
}

void	env_realloc(t_env **env)
{
	size_t	i;
	char	**new;

	(*env)->capacity *= 2;
	new = malloc(sizeof(char *) * (*env)->capacity);

	i = 0;
	while (i < (*env)->length)
	{
		new[i] = (*env)->vars[i];
		i += 1;
	}
	// here we just free parent pointer without children
	free((*env)->vars);
	(*env)->vars = new;
}

void	ft_swap(char **a, char **b)
{
	char *c = *a;
	*a = *b;
	*b = c;
}
void	env_add(t_env **env, char *var)
{
	t_env *e;
	if ((*env)->capacity == (*env)->length)
	{
		env_realloc(env);
	}
	e = *env;
	e->vars[e->length] = var;
	ft_swap(&e->vars[e->length], &e->vars[e->length - 1]);
	(*env)->length += 1;
}

void	env_sort(t_env *env)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (i < env->length)
	{
		j = 0;
		len = ft_strlen(env->vars[i]);
		while (j < env->length)
		{
			if (ft_strncmp(env->vars[i], env->vars[j], len) < 0)
			{
				t = env->vars[i];
				env->vars[i] = env->vars[j];
				env->vars[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
}

void	ms_env(t_env env)
{
	size_t	i;

	i = 0;
	while (i < env.length)
	{
		// TODO: make sure that var has \0
		if (ft_strchr(env.vars[i], '='))
			ft_printf("%s\n", env.vars[i]);
		i += 1;
	}
}