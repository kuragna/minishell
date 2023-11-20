/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:21:49 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:22:46 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

// TODO: extract VALUE from single quotes and double quotes

int	ms_export_(t_array *env, char *var)
{
	char	*end;
	int		i;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
	{
		return (ms_error("export: `%s\': not a valid identifier\n", var));
	}
	end = ft_strchr(var, '=');
	len = end - var;
	i = ms_get_idx(env, var);
	var = ft_strdup(var);
	if (i != -1)
	{
		free(env->items[i]);
		env->items[i] = var;
		return (0);
	}
	ms_array_append(env, var);
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
