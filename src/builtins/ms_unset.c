/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:59 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:12:19 by aabourri         ###   ########.fr       */
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
			return (ms_error("unset: `%s\': not a valid identifier\n", name));
		pos = ms_get_idx(env, name);
		if (pos != -1)
		{
			free(env->items[pos]);
			env->items[pos] = ft_strdup("");
		}
		i += 1;
	}
	return (0);
}
