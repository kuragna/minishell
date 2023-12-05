/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:21:49 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:49:31 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

static void	ms_env_append(t_array *env, char *var)
{
	size_t	i;

	i = 0;
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

static int	ms_export_(t_array *env, char *var)
{
	char	*substr;
	int		pos;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
		return (ms_error("minishell: export: `%s\': %s\n", var, MS_NVID));
	len = ft_strchr(var, '=') - var;
	substr = ft_substr(var, 0, (size_t)len);
	pos = ms_get_idx(env, substr);
	if (pos != -1 && len > 0)
	{
		free(substr);
		return (0);
	}
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

int	ms_export(int *fd)
{
	(void)fd;
	size_t	i;
	char	**items;
	int		status;

	i = 0;
	status = 0;
	items = g_ctx.items;
	if (*items == NULL)
		ms_export_print(*g_ctx.env);
	while (items[i])
	{
		if (ms_export_(g_ctx.env, items[i]))
			status = 1;
		i += 1;
	}
	return (status);
}
