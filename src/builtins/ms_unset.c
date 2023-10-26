#include "../../include/minishell.h"

// TODO: UNFINISHED
// TODO: unset must accepts array of strings
int	ms_unset(t_env *env, char *name)
{
	(void) env;
	(void) name;
	int		pos;
	size_t	i;

	if (*name == '\0')
		return (0);
	i = 0;
	if (!ms_start(*name) || !ms_symbol(name, 0))
	{
		return ms_error("unset: `%s\': not a valid identifier\n", name);
	}
	pos = ms_get_idx(env, name, ft_strlen(name));
	if (pos != -1)
	{
		// TODO: make it NULL
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup("");
	}
	return (0);
}

#if 0 
int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	t_env env = env_dup(envp);

	ms_export(&env, "NAME=VALUE");
	export_print(&env);
	ms_unset(&env, "ROWS");
	printf("-------------------------------\n");
	export_print(&env);
	return 0;
}

#endif 