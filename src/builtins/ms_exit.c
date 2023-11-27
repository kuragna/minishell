/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:19:08 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/27 19:50:56 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

#define ERR_MSG "numeric argument required"

int	ms_exit(char **argv, int argc)
{
	int		i;
	int		exit_status;

	i = 0;
	printf("exit\n");
	if (argc == 1)
		exit(0);
	while (argv[0][i] != '\0')
	{
		if (!ft_isdigit(argv[0][i]))
		{
			exit_status = 255;
			ms_error("minishell: exit: %s: %s\n", ERR_MSG, argv[0]);
			break ;
		}
		i++;
	}
	if (argc > 2 && argv[0][i] == '\0')
	{
		ms_error("minishell: exit: too many arguments\n");
		exit(1);
	}
	if (argv[0][i] == '\0')
		exit_status = ft_atoi(argv[0]) % 256;
	exit(exit_status);
}
