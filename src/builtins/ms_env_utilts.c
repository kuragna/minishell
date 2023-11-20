/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utilts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:18:13 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/20 18:42:58 by aabourri         ###   ########.fr       */
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

int	ms_get_idx(t_array *env, const char *var)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(var);
	while (i < env->len)
	{
		if (ft_strncmp(env->items[i], var, len) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

char	*ms_getenv(t_array *env, char *name)
{
	char	*var;
	int		pos;

	if (env == NULL)
		return (NULL);
	pos = ms_get_idx(env, name);
	if (pos == -1)
		return (NULL);
	var = ft_strchr(env->items[pos], '=');
	if (var == NULL)
		return (NULL);
	return (var + 1);
}
