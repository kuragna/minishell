/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:59 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 15:50:42 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_unset(t_data *data)
{
	char	**args;
	size_t	i;
	int		pos;
	int		status;

	i = 0;
	status = 0;
	args = data->argv + 1;
	while (args[i])
	{
		if (!ms_is_start(*args[i]) || !ms_symbol(args[i], 0))
		{
			ms_error("minishell: unset: `%s\': %s\n", args[i], MS_NVID);
			status = 1;
		}
		pos = ms_get_idx(data->env, args[i]);
		if (pos != -1)
		{
			free(data->env->items[pos]);
			data->env->items[pos] = NULL;
		}
		i += 1;
	}
	return (status);
}
