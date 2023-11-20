/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:00:32 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/20 18:18:16 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_open(const char *path, int oflag, int mode)
{
	int	fd;

	fd = open(path, oflag, mode);
	if (fd == -1)
	{
		ms_error("minishell: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	PERR("LINE: %d | FD: %d\n", __LINE__, fd);
	return (fd);
}

// int	ms_here_doc(const char *dlmtr)
// {
// 	char	*line;
// 	int		pp[2];

// 	if (pipe(pp) == -1)
// 	{
// 		ms_error("minishell: %s\n", strerror(errno));
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (ft_strncmp(line, dlmtr, ft_strlen(line)) == 0)
// 			break ;
// 		ft_putendl_fd(line, pp[MS_STDOUT]);
// 	}
// 	close(pp[MS_STDOUT]);
// 	return (pp[MS_STDIN]);
// }
//

// TODO: fix << with command not found

int	ms_here_doc(const char *dlmtr)
{
	char	*line;
	int		fd;

	fd = ms_open("here-doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line && ft_strncmp(line, dlmtr, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = ms_open("here-doc", O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	unlink("here-doc");
	return (fd);
}
