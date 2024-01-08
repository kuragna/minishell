/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:00:32 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/27 17:56:15 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ms_open(const char *path, int oflag, int mode)
{
	const int	fd = open(path, oflag, mode);

	if (fd == -1)
	{
		g_status = 1;
		ms_error("minishell: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (fd);
}

static int	ms_heredoc(const char *dlmtr, t_data *data)
{
	char	*line;
	char	*str;
	int		fd;

	fd = ms_open("/tmp/ms_here-doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd != -1 && 1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, dlmtr, ft_strlen(line) + 1 == 0))
		{
			free(line);
			break ;
		}
		str = line;
		if (!data->quotes_flag)
		{
			str = ms_heredoc_expansion(line, data);
			if (ft_strncmp(str, dlmtr, ft_strlen(str) + 1) == 0)
			{
				free(str);
				free(line);
				break ;
			}
		}
		ft_putendl_fd(str, fd);
		free(line);
	}
	close(fd);
	fd = ms_open("/tmp/ms_here-doc", O_RDONLY, 0);
	return (fd);
}

static int	ms_rdr_input(const char *path, t_token_type type, t_data *data)
{
	int	fd;

	fd = -1;
	if (type == DLESS)
	{
		fd = ms_heredoc(path, data);
	}
	if (type == LESS)
	{
		fd = ms_open(path, O_RDONLY, 0);
	}
	return (fd);
}

static int	ms_rdr_output(const char *path, t_token_type type)
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

// TODO: change return value to non-fd
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
			io[0] = ms_rdr_input(ptr->items[i].path, ptr->items[i].type, data);
			if (io[MS_STDIN] == -1)
				return (1);
			data->fd[MS_STDIN] = io[MS_STDIN];
		}
		if (ptr->items[i].type == DGREAT || ptr->items[i].type == GREAT)
		{
			io[1] = ms_rdr_output(ptr->items[i].path, ptr->items[i].type);
			if (io[MS_STDOUT] == -1)
				return (1);
			data->fd[MS_STDOUT] = io[MS_STDOUT];
		}
		ms_table_add(&data->table, io[MS_STDIN]);
		ms_table_add(&data->table, io[MS_STDOUT]);
	}
	return (0);
}
