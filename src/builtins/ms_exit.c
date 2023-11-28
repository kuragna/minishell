/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:19:08 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/28 15:42:33 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#define ERR_MSG "numeric argument required"


static int	ms_check_exit_status(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i += 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ms_error("minishell: exit: %s: %s\n", str, ERR_MSG);
			return (1);
		}
		i += 1;
	}
	return (0);
}


int	ms_exit(char **argv, const int argc)
{
	int		exit_status;

	printf("exit\n");
	if (argc == 1)
		exit(0);
	if (ms_check_exit_status(*argv))
		exit_status = 255;
	else if (argc > 2)
	{
		ms_error("minishell: exit: too many arguments\n");
		return (0);
	}
	else	
		exit_status = ft_atoi(*argv) % 256;
	exit(exit_status);
}
