#include "../include/minishell.h"

char	**ms_envcpy(t_array *env)
{
	size_t	i;
	t_array	e;

	i = 0;
	e = ms_array_init();
	if (!e.items)
		return (NULL);
	while (i < env->len)
	{
		if (ft_strchr(env->items[i], '='))
			ms_array_append(&e, env->items[i]);
		i += 1;
	}
	ms_array_append(&e, NULL);
	return (e.items);
}
