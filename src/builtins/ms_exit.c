/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:19:08 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:48:57 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#define ERR_MSG "numeric argument required"

static int	ms_check_exit_status(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i += 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ms_error("minishell: exit: %s: %s\n", str, ERR_MSG);
			return (1);
		}
		i += 1;
	}
	return (0);
}

static	int	ms_items_size(char **items)
{
	size_t	i;

	i = 0;
	while (items && items[i])
	{
		i += 1;
	}
	return (i);
}

int	ms_exit(int *fd)
{
	(void)fd;
	char	**argv = g_ctx.items;
	int		exit_status;
	int		argc = ms_items_size(argv) - 1;

	printf("exit\n");
	if (argc < 0)
		exit(0);
	if (ms_check_exit_status(*argv))
		exit_status = 255;
	else if (argc > 2)
	{
		ms_error("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_status = ft_atoi(*argv) % 256;
	exit(exit_status);
}
