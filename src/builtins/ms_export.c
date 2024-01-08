/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:21:49 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 15:42:23 by aabourri         ###   ########.fr       */
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

static void	ms_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ms_update_shlvl(t_array *env)
{
	char		*n;
	char		*s;
	int			pos;

	pos = ms_get_idx(env, "SHLVL");
	if (pos == -1)
	{
		s = ft_strdup("SHLVL=1");
		if (s)
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

	if (!ms_is_start(*var) || !ms_symbol(var + 1, '='))
		return (ms_error("minishell: export: `%s\': %s\n", var, MS_NVID));
	len = ft_strchr(var, '=') - var;
	substr = ft_substr(var, 0, (size_t)len);
	pos = ms_get_idx(env, substr);
	free(substr);
	if (len < 0 && pos != -1)
		return (0);
	var = ft_strdup(var);
	if (!var)
		return (0);
	if (pos != -1)
	{
		free(env->items[pos]);
		env->items[pos] = var;
		return (0);
	}
	ms_env_append(env, var);
	ms_swap(&env->items[env->len - 1], &env->items[env->len - 2]);
	return (0);
}

int	ms_export(t_data *data)
{
	size_t	i;
	char	**items;
	int		status;

	i = 0;
	status = 0;
	items = data->argv + 1;
	if (*items == NULL)
		ms_export_print(*data->env, data->fd);
	while (items[i])
	{
		if (ms_export_(data->env, items[i]))
			status = 1;
		i += 1;
	}
	return (status);
}
