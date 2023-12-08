/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:59 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/06 17:02:07 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_unset(int *fd)
{
	char	**args;
	size_t	i;
	int		pos;
	int		status;

	i = 0;
	status = 0;
	args = g_ctx.items;
	(void)fd;
	while (args[i])
	{
		if (!ms_start(*args[i]) || !ms_symbol(args[i], 0))
		{
			ms_error("minishell: unset: `%s\': %s\n", args[i], MS_NVID);
			status = 1;
		}
		pos = ms_get_idx(args[i]);
		if (pos != -1)
		{
			free(g_ctx.env->items[pos]);
			g_ctx.env->items[pos] = NULL;
		}
		i += 1;
	}
	return (status);
}
