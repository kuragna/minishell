/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:24:40 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/25 16:49:05 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cd(t_env *env, char *path)
{
	char *go;
	size_t	len;
	
	// TODO: replace go by path
	go = path;
	len = ft_strlen(path);
	if (*path == '\0')
	{
		go = ms_getenv(env, "HOME=");
		if (go == NULL)
			return ms_error ("cd: HOME not set\n");
	}
	else if (ft_strncmp(path, "-", len) == 0 || ft_strncmp(path, "--", len) == 0)
	{
		go = ms_getenv(env, "OLDPWD=");
		if (go == NULL)
			ms_error("cd: OLDPWD not set\n");
	}
	if ((*path == '~' && *(path + 1) == '\0') || (*path == '~' && *(path + 1) == '/'))
	{
		path += 1;
		go = ms_getenv(env, "HOME=");
		go = ft_strjoin(go, path);
		if (go == NULL)
			return ms_error("cd: HOME not set\n");
	}
	if (chdir(go) == -1)
	{
		return ms_error("cd: %s: %s\n", go, strerror(errno));
	}
	if (!env)
		return 1;
	go = ms_getenv(env, "PWD=");
	ms_export(env, ft_strjoin("OLDPWD=", go));
	ms_export(env, ft_strjoin("PWD=", getcwd(NULL, 0)));
	return 0;
}

#if 0


int	main(int argc, char **argv, char **envp)
{
	atexit(ms_leaks);
	(void) argc;
	(void) argv;
	(void) envp;
	
	t_env env = env_dup(envp);

	ms_cd(&env, "/"); // go to root
	ms_pwd();
	ms_cd(&env, "~"); // go home
	ms_pwd();
	ms_cd(&env, "-"); // go back to root
	ms_pwd();
	ms_cd(&env, "--"); // go back to home
	ms_pwd();
	ms_cd(&env, "../"); // go to previes dir
	ms_pwd();
	ms_cd(&env, ""); // go home
	ms_pwd();
	//ms_env(env);
	return 0;
}
#endif //






