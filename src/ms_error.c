/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:01:24 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 17:27:39 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ms_expected_token(const t_token_type type)
{
	const char	*tokens[] = {
		"newline",
		"|",
		"<",
		">",
		"<<",
		">>",
	};

	if (type > DGREAT)
		return (NULL);
	ms_error("minishell: %s `%s\'\n", SYTX_ERR, tokens[type]);
	return (NULL);
}

int	ms_error(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt += 1;
			if (*fmt == 's')
			{
				ft_putstr_fd(va_arg(ap, char *), MS_STDERR);
				fmt += 1;
			}
			else if (*fmt == 'c')
			{
				ft_putchar_fd(va_arg(ap, int), MS_STDERR);
				fmt += 1;
			}
		}
		write(MS_STDERR, fmt, 1);
		fmt += 1;
	}
	va_end(ap);
	return (1);
}

void	ms_exec_error(const char *cmd)
{
	int		fd;
	int		exit_status;
	char	*str;

	exit_status = MS_PD;
	str = strerror(errno);
	if (!ft_strchr(cmd, '/'))
	{
		exit_status = MS_CNF;
		str = "command not found";
	}
	else
	{
		fd = open(cmd, O_RDONLY | O_DIRECTORY);
		if (fd != -1)
		{
			errno = EISDIR;
			str = strerror(errno);
		}
		close(fd);
	}
	ms_error("minishell: %s: %s\n", cmd, str);
	exit(exit_status);
}
