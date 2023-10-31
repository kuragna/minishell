#include "../../include/minishell.h"


// TODO: multiple args without quotes must print space between them
// TODO: expand dollar sign
void	ms_echo(char **args)
{
	int		flag;
	size_t i = 0;
	int	space = 1;

	flag = 1;
	if (args[0] && ft_memcmp(args[0], "-n", ft_strlen(args[0])) == 0)
	{
		flag = 0;
		i += 1;
	}

	if (**args == '\'')
		space = 0;

	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (space && args[i + 1] != NULL)
			printf(" ");
		i += 1;
	}
	if (flag)
		printf("\n");
}
