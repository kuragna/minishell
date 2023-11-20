/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:33:09 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:34:15 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	if (waitpid(-1, NULL, 0) > 0)
		return ;
	rl_replace_line("", 0);
	write(MS_STDOUT, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	ms_catch_signal(void)
{
	int					err;
	struct sigaction	sa;

	sa.sa_handler = ms_sig_handler;
	sa.sa_flags = SA_RESTART;
	err = sigaction(SIGINT, &sa, NULL);
	if (err == -1)
	{
		return (ms_error("minishell: %s: %s\n", strerror(errno)));
	}
	err = sigaction(SIGQUIT, &sa, NULL);
	if (err == -1)
	{
		return (ms_error("minishell: %s: %s\n", strerror(errno)));
	}
	return (0);
}
