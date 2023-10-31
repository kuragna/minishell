#include "../../include/ms_builtin.h"

int	ms_echo(char **args)
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

	// not safe
	if (args[0] && **args == '\'')
		space = 0;

	while (args[i] != NULL)
	{
		ft_printf("[%s]", args[i]);
		if (space && args[i + 1] != NULL)
			ft_printf(" ");
		i += 1;
	}
	if (flag)
		ft_printf("\n");
	return (0);
}
