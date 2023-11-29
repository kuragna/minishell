/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:59 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/29 16:49:03 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_unset(t_array *env, char **args)
{
	size_t	i;
	int		pos;
	char	*name;

	i = 0;
	while (args[i])
	{
		name = args[i];
		if (!ms_start(*name) || !ms_symbol(name, 0))
		{
			ms_error("minishell: unset: `%s\': %s\n", name, MS_NVID);
			return (1);
		}
		pos = ms_get_idx(env, name);
		if (pos != -1)
		{
			free(env->items[pos]);
			env->items[pos] = NULL;
		}
		i += 1;
	}
	return (0);
}
