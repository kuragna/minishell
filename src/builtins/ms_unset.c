/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:59 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:50:06 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_unset(int *fd)
{
	(void)fd;
	char	**args;
	size_t	i;
	int		pos;
	int		status;
	char	*name;

	i = 0;
	status = 0;
	args = g_ctx.items;
	while (args[i])
	{
		name = args[i];
		if (!ms_start(*name) || !ms_symbol(name, 0))
		{
			ms_error("minishell: unset: `%s\': %s\n", name, MS_NVID);
			status = 1;
		}
		pos = ms_get_idx(g_ctx.env, name);
		if (pos != -1)
		{
			free(g_ctx.env->items[pos]);
			g_ctx.env->items[pos] = NULL;
		}
		i += 1;
	}
	return (status);
}
