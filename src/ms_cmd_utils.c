/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_utilts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:56:56 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 17:13:43 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**ms_get_paths(void)
{
	const char	*path = ms_getenv(g_ctx.env, "PATH");
	char		**paths;

	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*ms_path_suffix(char *path, char *cmd)
{
	char	*slash;

	slash = ft_strjoin(path, "/");
	if (slash)
	{
		path = ft_strjoin(slash, cmd);
		free(slash);
	}
	return (path);
}

int	ms_cmd_path(char **cmd)
{
	int		i;
	int		re;
	char	*cmd_path;
	char	**paths;

	if (ft_strncmp(*cmd, "./", 2) == 0 || ft_memchr(*cmd, '/', 1))
		return (1);
	i = 0;
	paths = ms_get_paths();
	if (paths == NULL)
		return (0);
	while (paths[i] != NULL)
	{
		cmd_path = ms_path_suffix(paths[i], *cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			*cmd = cmd_path;
			break ;
		}
		free(cmd_path);
		i += 1;
	}
	re = paths[i] != NULL;
	ft_free(paths);
	return (re);
}

char	*ms_str_tolower(const char *str)
{
	char	*dup;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
		return ((char *)str);
	while (dup[i])
	{
		dup[i] = ft_tolower(dup[i]);
		i += 1;
	}
	return (dup);
}
