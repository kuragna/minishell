#include "../include/minishell.h"

char	**ms_get_paths(void)
{
	const char	*path = getenv("PATH");
	char	**paths;

	paths = ft_split(path, ':'); // error
	return paths;
}

char	*ms_path_prefix(char *path, char *cmd)
{
	char	*slash = ft_strjoin(path, "/");
	char	*p_path = ft_strjoin(slash, cmd);
	return p_path;
}

int	ms_cmd_path(char **cmd)
{
	char	*cmd_path;
	char	**paths = ms_get_paths();
	size_t	i = 0;

	if (ft_strchr(*cmd, '/'))
		return (1);

	while (paths[i] != NULL)
	{
		cmd_path = ms_path_prefix(paths[i], *cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			*cmd = cmd_path;
			break ;
		}
		i += 1;
	}
	if (paths[i] == NULL)
		return 0;
	return 1;
}

void	ms_exec(char *cmd, char **args)
{
	if (ms_cmd_path(&cmd) == 0)
	{
		MS_ERROR("minishell: ", cmd, ": command not found");
		exit(MS_CNF);
	}
	execve(cmd, args, NULL);
}

