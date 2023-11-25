/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:21:49 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/25 15:19:21 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

// TODO: extract VALUE from single quotes and double quotes


static void	ms_env_append(t_array *env, char *var)
{
	size_t i = 0;

	while (i < env->len)
	{
		if (env->items[i] == NULL)
		{
			env->items[i] = var;
			return ;
		}
		i += 1;
	}
	ms_array_append(env, var);
}

void	ms_update_shlvl(t_array *env)
{
	char		*n;
	char		*s;
	int			pos;

	pos = ms_get_idx(env, "SHLVL");
	if (pos == -1)
	{
		s = "SHLVL=1";
		ms_env_append(env, s);
		return ;
	}
	s = ft_strchr(env->items[pos], '=');
	n = ft_itoa(ft_atoi(s + 1) + 1);
	s = ft_strjoin("SHLVL=", n);
	if (!s)
		return ;
	free(n);
	free(env->items[pos]);
	env->items[pos] = s;
}

int	ms_export_(t_array *env, char *var)
{
	char	*substr;
	int		pos;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
	{
		ms_error("minishell: export: `%s\': not a valid identifier\n", var);
		return (1);
	}
	substr = ft_strchr(var, '=');
	len = substr - var;
	substr = ft_substr(var, 0, (size_t)len);
	pos = ms_get_idx(env, substr);
	// TODO: why we need strdup here?
	var = ft_strdup(var);
	free(substr);
	if (pos != -1)
	{
		free(env->items[pos]);
		env->items[pos] = var;
		return (0);
	}
	ms_env_append(env, var);
	return (0);
}

static void	ms_export_print(t_array env)
{
	size_t	i;

	i = 0;
	ms_env_sort(env);
	while (i < env.len)
	{
		if (env.items[i][0])
			printf("declare -x %s\n", env.items[i]);
		i += 1;
	}
}

int	ms_export(t_array *env, char **items)
{
	size_t	i;

	i = 0;
	if (*items == NULL)
		ms_export_print(*env);
	while (items[i])
	{
		ms_export_(env, items[i]);
		i += 1;
	}
	return (0);
}
