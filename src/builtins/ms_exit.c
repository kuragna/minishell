/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:19:08 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/12 13:11:08 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

int	ms_exit_check(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i += 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ms_error("minishell: exit: %s: %s\n", str, MS_NAR);
			return (1);
		}
		i += 1;
	}
	return (0);
}

static int	ms_exit_count(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
	{
		count += 1;
	}
	return (count);
}

int	ms_exit(t_data *data)
{
	int		count;
	int		exit_status;
	char	**argv;

	exit_status = 0;
	argv = data->argv + 1;
	ft_putendl_fd("exit", data->fd[MS_STDOUT]);
	count = ms_exit_count(argv);
	if (count > 0 && ms_exit_check(*argv))
		exit_status = 255;
	else if (count > 1)
	{
		ms_error("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_status = ft_atoi(*argv) % 256;
	if (!data->flag)
		exit(exit_status);
	return (0);
}
