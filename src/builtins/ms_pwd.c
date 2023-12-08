/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:24:14 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:59:44 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

int	ms_pwd(int *fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		return (ms_error("minishell: %s\n", strerror(errno)));
	}
	(void)fd;
	printf("%s\n", path);
	free(path);
	return (0);
}
