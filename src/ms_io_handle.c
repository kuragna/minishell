/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:00:32 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 19:24:01 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ms_open(const char *path, int oflag, int mode)
{
	const int	fd = open(path, oflag, mode);

	if (fd == -1)
	{
		ms_error("minishell: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (fd);
}

static int	ms_here_doc(const char *dlmtr)
{
	char	*line;
	int		fd;

	fd = ms_open("/tmp/ms_here-doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line && ft_strncmp(line, dlmtr, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = ms_open("/tmp/ms_here-doc", O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	unlink("/tmp/ms_here-doc");
	return (fd);
}

static int	ms_redir_input(const char *path, const t_token_type type)
{
	int	fd;

	fd = -1;
	if (type == DLESS)
	{
		fd = ms_here_doc(path);
	}
	if (type == LESS)
	{
		fd = ms_open(path, O_RDONLY, 0);
	}
	return (fd);
}

static int	ms_redir_output(const char *path, const t_token_type type)
{
	int	fd;

	if (type == GREAT)
	{
		fd = ms_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (type == DGREAT)
	{
		fd = ms_open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (fd);
}

int	ms_io_handle(struct s_redirs *ptr, t_data *data)
{
	int		io[2];
	size_t	i;

	i = -1;
	ft_memset(io, -1, sizeof(io));
	while (++i < ptr->len)
	{
		if (ptr->items[i].type == DLESS || ptr->items[i].type == LESS)
		{
			io[0] = ms_redir_input(ptr->items[i].path, ptr->items[i].type);
			if (io[MS_STDIN] == -1)
				return (1);
			data->fd[MS_STDIN] = io[MS_STDIN];
		}
		if (ptr->items[i].type == DGREAT || ptr->items[i].type == GREAT)
		{
			io[1] = ms_redir_output(ptr->items[i].path, ptr->items[i].type);
			if (io[MS_STDOUT] == -1)
				return (1);
			data->fd[MS_STDOUT] = io[MS_STDOUT];
		}
		ms_table_add(&data->table, io[MS_STDIN]);
		ms_table_add(&data->table, io[MS_STDOUT]);
	}
	return (0);
}
