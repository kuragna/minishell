/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:15:29 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:15:29 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#include <stdio.h>

static	int	ms_check_opt(char *opt)
{
	if (*opt == '-')
		opt += 1;
	while (*opt)
	{
		if (*opt == 'n')
			opt += 1;
		else
			return (0);
	}
	return (1);
}
// TODO: use printf for stdin/out change them in child process

int	ms_echo(char **args, int *fd)
{
	int		flag;
	size_t	i;

	i = 0;
	flag = 1;
	if (*args && ms_check_opt(*args))
	{
		i += 1;
		flag = 0;
	}
	while (args && args[i] != NULL)
	{
		ft_putstr_fd(args[i], fd[MS_STDOUT]);
		if (args[i + 1])
			ft_putstr_fd(" ", fd[MS_STDOUT]);
		i += 1;
	}
	if (flag)
		ft_putstr_fd("\n", fd[MS_STDOUT]);
	if (fd[MS_STDOUT] > 1)
		close(fd[MS_STDOUT]);
	return (0);
}
