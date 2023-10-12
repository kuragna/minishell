#include "../../include/minishell.h"

void	ms_exit(char *line)
{
	if (!line || ft_strncmp(line, "exit", 4) == 0)
	{
		ft_putendl_fd("exit", MS_STDOUT);
		exit(EXIT_SUCCESS);
	}
} 