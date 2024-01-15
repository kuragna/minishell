/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:12:41 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/15 14:41:08 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

static int	ms_set_pwd(t_array *env, const char *go)
{
	char	*str[2];
	int		pos;

	pos = ms_get_idx(env, "OLDPWD");
	if (pos == -1)
		return (ms_error("minishell: cd: OLDPWD not set\n"));
	str[0] = ft_strjoin("OLDPWD=", go);
	if (!str[0])
		return (1);
	free(env->items[pos]);
	env->items[pos] = str[0];
	pos = ms_get_idx(env, "PWD");
	if (pos != -1)
	{
		str[1] = getcwd(NULL, 0);
		if (!str[1])
			return (1);
		str[0] = ft_strjoin("PWD=", str[1]);
		free(str[1]);
		if (!str[0])
			return (1);
		free(env->items[pos]);
		env->items[pos] = str[0];
	}
	return (0);
}

static char	*ms_cd_(t_array *env, const char *path)
{
	const size_t	len = ft_strlen(path);
	char			*go;

	go = (char *)path;
	if (!path)
	{
		go = ms_getenv(env, "HOME");
		if (!go)
		{
			ms_error("minishell: cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strncmp(path, "-", len) == 0
		|| ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD");
		if (!go)
		{
			ms_error("minishell: cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	return (go);
}

int	ms_cd(t_data *data)
{
	const char		*path = *(data->argv + 1);
	char			*go;
	DIR				*dir;

	go = ms_cd_(data->env, path);
	if (!go || data->pipe_flag)
	{
		if (go && path)
		{
			dir = opendir(path);
			if (dir == NULL)
				return (ms_error("minishell: cd: %s: %s\n",
						path, strerror(errno)));
			if (dir)
				closedir(dir);
		}
		return (0);
	}
	if (chdir(go) == -1)
		return (ms_error("minishell: cd: %s: %s\n", path, strerror(errno)));
	go = ms_getenv(data->env, "PWD");
	if (ms_set_pwd(data->env, go))
		return (1);
	return (0);
}
