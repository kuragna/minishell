#include "../../include/minishell.h"

static int	ms_unset_(t_env *env, char *name)
{
	int		pos;
	size_t	i;

	i = 0;
	if (!ms_start(*name) || !ms_symbol(name, 0))
	{
		return ms_error("unset: `%s\': not a valid identifier\n", name);
	}
	pos = ms_get_idx(env, name, ft_strlen(name));
	if (pos != -1)
	{
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup("");
	}
	return (0);
}

int	ms_unset(t_env *env, char **args)
{
	size_t i;

	i = 0;
	while (args[i])
	{
		ms_unset_(env, args[i]);
		i += 1;
	}
	return (0);
}