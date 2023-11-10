#include "../include/minishell.h"

char	**ms_get_paths(void)
{
	const char	*path = getenv("PATH");
	char	**paths;

	paths = ft_split(path, ':');
	return (paths);
}


char	*ms_path_suffix(char *path, char *cmd)
{
	char	*slash;

	slash = ft_strjoin(path, "/");
	path = ft_strjoin(slash, cmd);
	free(slash);
	return (path);
}

int	ms_cmd_path(char **cmd)
{
	char	*cmd_path;
	char	**paths;
	size_t	i;

	if (ft_strncmp(*cmd, "./", 2) == 0 || ft_strchr(*cmd, '/'))
	{
		return (1);
	}
	i =  0;
	paths = ms_get_paths();
	while (paths[i] != NULL)
	{
		cmd_path = ms_path_suffix(paths[i], *cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			*cmd = cmd_path;
			break ;
		}
		i += 1;
	}
	return (paths[i] != NULL);
}

#if 1

int	ms_interactive_mode(void)
{
	struct termios attr;

	if (!isatty(MS_STDIN))
	{
		return ms_error("minishell: %s\n", strerror(errno)); 
	}
	if (tcgetattr(MS_STDIN, &attr) == -1)
	{
		return ms_error("minishell: %s: %s\n", strerror(errno));
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(MS_STDIN, TCSANOW, &attr) == -1)
	{
		return ms_error("minishell: %s: %s\n", strerror(errno));
	}
	return (0);
}


char	*ms_getenv(t_env *env, char *name)
{
	char	*var;
	int		pos;

	if (env == NULL)
		return (NULL);
	pos = ms_get_idx(env, name, ft_strlen(name));
	if (pos == -1)
		return (NULL);
	var =  ft_strchr(env->vars[pos], '=');
	if (var == NULL)
		return (NULL);
	return (var + 1);
}


#endif
