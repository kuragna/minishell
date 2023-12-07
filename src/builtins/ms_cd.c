/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:12:41 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/07 16:09:25 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

static int	ms_set_pwd(char *go)
{
	char	*str[2];
	int		pos;

	pos = ms_get_idx("OLDPWD");
	if (pos == -1)
		return (ms_error("minishell: cd: OLDPWD not set\n"));
	str[0] = ft_strjoin("OLDPWD=", go);
	if (!str[0])
		return (1);
	free(g_ctx.env->items[pos]);
	g_ctx.env->items[pos] = str[0];
	pos = ms_get_idx("PWD");
	if (pos != -1)
	{
		str[1] = getcwd(NULL, 0);
		if (!str[1])
			return (1);
		str[0] = ft_strjoin("PWD=", str[1]);
		free(str[1]);
		if (!str[0])
			return (1);
		free(g_ctx.env->items[pos]);
		g_ctx.env->items[pos] = str[0];
	}
	return (0);
}

static char	*ms_cd_(const char *path)
{
	const size_t	len = ft_strlen(path);
	char			*go;

	go = (char *)path;
	if (!path)
	{
		go = ms_getenv("HOME");
		if (!go)
		{
			ms_error("minishell: cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strncmp(path, "-", len) == 0
		|| ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv("OLDPWD");
		if (!go)
		{
			ms_error("minishell: cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	return (go);
}

int	ms_cd(int *fd)
{
	const char		*path = *g_ctx.items;
	char			*go;
	DIR				*dir;

	(void)fd;
	go = ms_cd_(path);
	if (!go || g_ctx.flag)
	{
		if (go && path)
		{
			dir = opendir(path);
			if (dir == NULL)
				ms_error("minishell: cd: %s: %s\n", path, strerror(errno));
			if (dir)
				closedir(dir);
		}
		return (1);
	}
	if (chdir(go) == -1)
		return (ms_error("minishell: cd: %s: %s\n", path, strerror(errno)));
	go = ms_getenv("PWD");
	if (ms_set_pwd(go))
		return (1);
	return (0);
}
