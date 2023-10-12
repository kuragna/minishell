/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:24:40 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/12 19:33:28 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_var_pos(t_env *env, char *var)
{
	size_t i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (i < env->lenght && env->vars[i])
	{
		if (ft_strncmp(env->vars[i], var, len) == 0)
		{
			return (i);
		}
		i += 1;
	}
	return (-1);
}

int	ms_cd(t_env *env, char *path)
{
	char	*str;
	int	err;
	int	i;
	int	j;

	if (ft_strncmp(path, "-", 1) == 0)
	{
		j = ms_var_pos(env, "OLDPWD");
		if (j == -1)
		{
			MS_ERROR("cd: OLDPWD not set", "", "");
			return (1);
		}
		path = &env->vars[j][7];
	}
	if (!*path)
	{
		i = ms_var_pos(env, "HOME=");
		if (i == -1)
		{
			MS_ERROR("cd: HOME not set", "", "");
			return (1);
		}
		path = &env->vars[i][5];
	}
	err = chdir(path);
	if (err == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}

	/* check if function return -1 */
	i = ms_var_pos(env, "PWD=");
	j = ms_var_pos(env, "OLDPWD=");

	str = &env->vars[i][4]; //getcwd(NULL, 0); // check error
	ft_strlcpy(&env->vars[j][7], &env->vars[i][4], ft_strlen(&env->vars[i][3]));
	ft_strlcpy(&env->vars[i][4], str, ft_strlen(str) + 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	
	t_env env = env_dup(envp);

	(void)env;

	size_t i;

	i = 0;

	ms_cd(&env, "");
	
	if (fork() == 0)
	{
		char *path = "/bin/pwd";
		char *args[] = {
			"pwd",
			NULL,
		};
		int err = execve(path, args, env.vars);
		if (err == -1)
		{
			perror("Error");
		}
	}
	waitpid(-1, NULL, 0);
	
	return 0;
}
