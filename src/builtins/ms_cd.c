/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:12:41 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:47:58 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

// TODO: replace this function
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
// TODO: print pwd after cd -

int	ms_cd(int *fd)
{
	(void)fd;
	t_array *env = g_ctx.env;
	char	*go;
	size_t	len;
	char	*path = *g_ctx.items; // has NULL

	go = path;
	len = ft_strlen(path);
	if (!path)
	{
		go = ms_getenv(env, "HOME");
		if (!go)
			return (ms_error ("minishell: cd: HOME not set\n"));
	}
	else if (ft_strncmp(path, "-", len) == 0 || ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD");
		if (!go)
			return (ms_error("minishell: cd: OLDPWD not set\n"));
	}
	if (chdir(go) == -1)
		return (ms_error("minishell: cd: %s: %s\n", path, strerror(errno)));
	go = ms_getenv(env, "PWD");
	ms_set_pwd(env, ft_strjoin("OLDPWD=", go), ms_get_idx(env, "OLDPWD"));
	ms_set_pwd(env, ft_strjoin("PWD=", getcwd(NULL, 0)), ms_get_idx(env, "PWD"));
	return (0);
}
