/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utilts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:18:13 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/06 17:01:45 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"
#include <stdlib.h>

int	ms_start(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	ms_symbol(char *str, int c)
{
	while (*str && *str != c)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str += 1;
	}
	return (1);
}

int	ms_get_idx(const char *var)
{
	t_array	*env;
	char	*str;
	size_t	len;
	size_t	sz;
	size_t	i;

	if (!var)
		return (-1);
	i = 0;
	sz = ft_strlen(var);
	env = g_ctx.env;
	while (i < env->len && env->items[i])
	{
		str = ft_strchr(env->items[i], '=');
		len = str - env->items[i];
		if (!str)
			len = ft_strlen(env->items[i]);
		if (sz == len)
		{
			if (ft_strncmp(env->items[i], var, len) == 0)
				return (i);
		}
		i += 1;
	}
	return (-1);
}

// char	*ms_getenv(t_array *env, const char *name)
char	*ms_getenv(const char *name)
{
	t_array	*env;
	char	*var;
	int		pos;

	env = g_ctx.env;
	if (env->len == 0)
		return (NULL);
	pos = ms_get_idx(name);
	if (pos == -1)
		return (NULL);
	var = ft_strchr(env->items[pos], '=');
	if (!var)
		return (NULL);
	return (var + 1);
}

char	**ms_env_sort(char **envp)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (envp[i])
	{
		j = 0;
		len = ft_strlen(envp[i]);
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], len) < 0)
			{
				t = envp[i];
				envp[i] = envp[j];
				envp[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
	return (envp);
}
