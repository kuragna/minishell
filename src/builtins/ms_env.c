#include "../../include/minishell.h"

/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * 
 * */
void	ms_env(t_env env)
{
	size_t	i;

	i = 0;
	while (i < env.lenght && env.vars[i])
	{
		// TODO: make sure that var has \0
		if (ft_strchr(env.vars[i], '='))
			printf("%s\n", env.vars[i]);
		i += 1;
	}
}