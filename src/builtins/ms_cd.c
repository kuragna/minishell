/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:12:41 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:13:49 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#include <assert.h>

static int	ms_set_pwd(t_array *env, char *name, int pos)
{
	if (!name)
		return (1);
	if (pos == -1)
		return (ms_error("cd: %s not set\n"));
	free(env->items[pos]);
	env->items[pos] = name;
	return (0);
}

// TODO: simplify this function

int	ms_cd(t_array *env, char *path)
{
	char	*go;
	size_t	len;

	if (!env->items)
		return (1);
	go = path;
	len = ft_strlen(path);
	if (!path)
	{
		go = ms_getenv(env, "HOME");
		if (!go)
			return (ms_error ("cd: HOME not set\n"));
	}
	else if (ft_strncmp(path, "-", len) == 0 || ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD");
		if (!go)
			return (ms_error("cd: OLDPWD not set\n"));
	}
	else if (ft_strncmp(path, "~", 1) == 0 || ft_strncmp(path, "~/", 2) == 0)
	{
		go = ms_getenv(env, "HOME");
		go = ft_strjoin(go, path + 1);
		if (!go)
			return (ms_error("cd: HOME not set\n"));
	}
	if (chdir(go) == -1)
		return (ms_error("cd: %s: %s\n", path, strerror(errno)));
	// NOTE: dont remove equal for strjoin
	go = ms_getenv(env, "PWD");
	ms_set_pwd(env, ft_strjoin("OLDPWD=", go), ms_get_idx(env, "OLDPWD"));
	ms_set_pwd(env, ft_strjoin("PWD=", getcwd(NULL, 0)), ms_get_idx(env, "PWD"));
	return (0);
}
