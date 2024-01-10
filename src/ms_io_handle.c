/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:00:32 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/09 19:36:52 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define MS_PERMS	0644

extern int	g_status;

int	ms_open(const char *path, int oflag, int mode)
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

void	ms_heredoc(const int fd, const char *dlmtr, t_data *data)
{
	char	*strs[2];

	while (fd != -1 && 1)
	{
		strs[1] = readline("> ");
		if (!strs[1] || ft_strncmp(strs[1], dlmtr, ft_strlen(strs[1]) + 1) == 0)
		{
			free(strs[1]);
			break ;
		}
		strs[0] = strs[1];
		if (!data->quotes_flag)
		{
			strs[0] = ms_heredoc_expansion(strs[1], data);
			if (ft_strncmp(strs[0], dlmtr, ft_strlen(strs[0]) + 1) == 0)
			{
				free(strs[0]);
				free(strs[1]);
				break ;
			}
		}
		ft_putendl_fd(strs[0], fd);
		free(strs[1]);
	}
}

static int	ms_rdr_input(const char *path, t_token_type type, t_data *data)
{
	int			fd;

	fd = -1;
	if (type == DLESS)
	{
		fd = ms_heredoc_child("/tmp/ms_heredoc", (char *)path, data);
	}
	if (type == LESS)
		fd = ms_open(path, O_RDONLY, 0);
	return (fd);
}

static int	ms_rdr_output(const char *path, t_token_type type)
{
	int	fd;

	if (type == GREAT)
	{
		fd = ms_open(path, O_WRONLY | O_CREAT | O_TRUNC, MS_PERMS);
	}
	if (type == DGREAT)
	{
		fd = ms_open(path, O_WRONLY | O_CREAT | O_APPEND, MS_PERMS);
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
