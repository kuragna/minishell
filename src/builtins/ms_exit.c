#include "../../include/minishell.h"

void	ms_exit(void)
{
	ft_putendl_fd("exit", MS_STDOUT);
	exit(EXIT_SUCCESS);
} 