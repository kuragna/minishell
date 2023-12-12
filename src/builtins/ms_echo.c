/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:15:29 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 15:40:57 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#include <stdio.h>

static int	ms_check_opt(char **argv)
{
	char	*arg;
	size_t	i;

	if (!*argv || argv[0][0] != '-')
		return (0);
	i = 0;
	while (argv[i])
	{
		arg = argv[i];
		if (*arg == '-' && *(arg + 1) == 'n')
			arg += 1;
		while (*arg && *arg == 'n')
			arg += 1;
		if (*arg != '\0')
			return (i);
		i += 1;
	}
	return (i);
}

int	ms_echo(t_data *data)
{
	char	**args;
	int		flag;
	size_t	i;

	i = 0;
	args = data->argv + 1;
	flag = ms_check_opt(args);
	i = flag;
	while (args && args[i] != NULL)
	{
		ft_putstr_fd(args[i], data->fd[MS_STDOUT]);
		if (args[i + 1])
			ft_putstr_fd(" ", data->fd[MS_STDOUT]);
		i += 1;
	}
	if (!flag)
		ft_putstr_fd("\n", data->fd[MS_STDOUT]);
	return (0);
}
