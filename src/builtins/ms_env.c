#include "../../include/minishell.h"

/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * 
 * */

void	add_env(t_env *env, char *var);

t_env env_dup(char **envp)
{
	size_t	i;
	char	*str;
	t_env	env;

	i = 0;
	env.length = 0;
	env.capacity = 16;
	env.vars = malloc(sizeof(char *) * env.capacity); // check error
	while (envp[i] != NULL)
	{
		str = ft_strdup(envp[i]);
		env_add(&env, str);
		i += 1;
	}
	return env;
}


void	ft_swap(char **a, char **b)
{
	char *c = *a;
	*a = *b;
	*b = c;
}

void	env_add(t_env *env, char *var)
{
	if (env->capacity == env->length)
	{
		env->capacity *= 2;
		env->vars = ft_realloc(env->vars, sizeof(char *) * env->capacity);
	}
	env->vars[env->length] = var;
	env->length += 1;
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



#if 0

void	find_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{

	atexit(find_leaks);
	(void) argc;
	(void) argv;
	(void) envp;


	t_env env = env_dup(envp);

	printf("CAP: %ld\n", env.capacity);
	printf("LEN: %ld\n", env.length);




	(void)env;


	printf("from env\n");
	return 0;
}
#endif