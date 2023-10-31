#include "../../include/minishell.h"

int ms_pwd(void)
{
	char	*path = getcwd(NULL, 0);
	if (path == NULL)
	{
		return ms_error("minishell: %s\n", strerror(errno));
	}
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

