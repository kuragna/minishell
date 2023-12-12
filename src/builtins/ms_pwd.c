/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:24:14 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 15:57:46 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

int	ms_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		return (ms_error("minishell: %s\n", strerror(errno)));
	}
	ft_putendl_fd(path, data->fd[MS_STDOUT]);
	free(path);
	return (0);
}
