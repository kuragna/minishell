/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:15:57 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/29 17:23:09 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

t_array	ms_env_dup(char **envp)
{
	t_array	array;
	size_t	i;
	char	*str;

	i = 0;
	array = ms_array_init();
// 	if (!envp || !*envp)
// 		ms_array_append(&array, NULL);
	while (envp[i] != NULL)
	{
		str = ft_strdup(envp[i]);
		if (str)
			ms_array_append(&array, str);
		i += 1;
	}
	ms_array_append(&array, NULL);
	return (array);
}

void	ms_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ms_env_sort(t_array env)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (i < env.len - 1)
	{
		j = 0;
		len = ft_strlen(env.items[i]);
		while (j < env.len - 1)
		{
			if (ft_strncmp(env.items[i], env.items[j], len) < 0)
			{
				t = env.items[i];
				env.items[i] = env.items[j];
				env.items[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
}

int	ms_env(t_array env, int *fd)
{
	size_t	i;

	i = 0;
	while (i < env.len)
	{
		if (env.items[i])
			ft_putendl_fd(env.items[i], fd[MS_STDOUT]);
		i += 1;
	}
	return (0);
}
