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
		free(cmd_path);
		i += 1;
	}
	ft_free(paths);
	return (paths[i] != NULL);
}

