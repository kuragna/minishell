#include "../include/minishell.h"

int ms_pwd(void)
{
	char	*path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ms_error(path, MS_ERR);
		return (1);
	}
	ft_printf("%s\n", path);
	free(path);
	return (0);
}


void	ms_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_printf("%s\n", environ[i]);
		i += 1;
	}	
}

void	ms_cd(void)
{
	assert(0 && "TODO: cd not implemented yet");
}

void	ms_unset(void)
{
	assert(0 && "TODO: unset not implemented yet");
}

void	ms_export(void)
{
	assert(0 && "TODO: export not implemented yet");
}
