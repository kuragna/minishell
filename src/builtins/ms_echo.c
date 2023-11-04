#include "../../include/ms_builtin.h"

#include <stdio.h>

static	int	ms_check_opt(char *opt)
{
	if (*opt == '-')
		opt += 1;
	while (*opt)
	{
		if (*opt == 'n')
			opt += 1;
		else
			return (0);
	}
	return (1);
}

int	ms_echo(char **args)
{
	int		flag;
	size_t	i;

	i = 0;
	flag = 1;
	if (*args && ms_check_opt(*args))
	{
		i += 1;
		flag = 0;
	}
	while (args && args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i += 1;
	}
	if (flag)
		ft_printf("\n");
	return (0);
}
