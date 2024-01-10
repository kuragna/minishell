/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:24:14 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/10 12:58:26 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

static int	ms_pwd_opts(char *str)
{
	size_t	i;

	i = 0;
	while (i < 2 && str[i])
	{
		if (str[i] != '-')
			break ;
		i += 1;
	}
	if (str[i] != '\0')
	{
		ms_error("minishell: pwd: ");
		i = -1;
		while (++i < 2 && str[i])
			write(MS_STDERR, &str[i], 1);
		ms_error(": invalid option\n");
		return (1);
	}
	return (0);
}

int	ms_pwd(t_data *data)
{
	size_t	i;
	char	*path;

	i = 0;
	if (data->argv[1])
	{
		if (ms_pwd_opts(data->argv[1]))
			return (1);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		return (ms_error("minishell: %s\n", strerror(errno)));
	}
	ft_putendl_fd(path, data->fd[MS_STDOUT]);
	free(path);
	return (0);
}
