/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:33:09 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/07 17:03:39 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define MS_SIG_SIZE 3

void	ms_signal_handler(int sig)
{
	if (sig != SIGINT)
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

int	ms_signal(void)
{
	size_t				i;
	int					err;
	struct sigaction	sa;
	const int			sigs[MS_SIG_SIZE] = {SIGINT, SIGQUIT, SIGTSTP};

	i = 0;
	sa.sa_handler = ms_signal_handler;
	sa.sa_flags = SA_RESTART;
	while (i < MS_SIG_SIZE)
	{
		err = sigaction(sigs[i], &sa, NULL);
		if (err == -1)
		{
			ms_error("minishell: %s\n", strerror(errno));
			return (1);
		}
		i += 1;
	}
	return (0);
}

int	ms_interactive_mode(void)
{
	struct termios	attr;

	if (!isatty(MS_STDIN))
	{
		return (1);
	}
	if (tcgetattr(MS_STDIN, &attr) == -1)
	{
		return (1);
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(MS_STDIN, TCSANOW, &attr) == -1)
	{
		return (1);
	}
	return (0);
}
