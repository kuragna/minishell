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

struct s_string ms_heredoc_expansion(const char *name, t_data *data)
{
	char	*s;
	struct s_string word;
	struct s_string dollar;

	word = ms_string_init();
	dollar = ms_string_init();
	while (name && *name)
	{
		if (*name == '$')
		{
			dollar.len = 0;
			name += 1;
			while (*name && ms_is_usalnum(*name))
			{
				ms_char_append(&dollar, *name);
				name += 1;
			}
			ms_char_append(&dollar, '\0');
			s = ms_getenv(data->env, dollar.data);
			ms_str_append(&word, s);
		}
		if (!*name)
			break ;
		ms_char_append(&word, *name);
		name += 1;
	}
	free(dollar.data);
	return (ms_char_append(&word, '\0'), word);
}

static int	ms_here_doc(const char *dlmtr, t_data *data)
{
	char	*line;
	struct s_string str;
	int		fd;

	fprintf(stderr, "dlmtr: `%s`\n", dlmtr);
	fd = ms_open("/tmp/ms_here-doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (!dlmtr)
		dlmtr = "";
	while (1)
	{
		line = readline("> ");
		// TODO: make one condition
		if (!line)
			break ;
		if (*line && ft_strncmp(line, dlmtr, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		str = ms_heredoc_expansion(line, data);
		if (ft_strncmp(str.data, dlmtr, str.len) == 0)
		{
			free(str.data);
			free(line);
			break ;
		}
		ft_putendl_fd(str.data, fd);
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
	/* if (type == DLESS)
	{
		fd = ms_here_doc(path);
	} */
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
		if (ptr->items[i].type == DLESS)
		{
			io[0] = ms_here_doc(ptr->items[i].path, data);
			if (io[MS_STDIN] == -1)
				return 1;
			data->fd[MS_STDIN] = io[MS_STDIN];
		}
		if (ptr->items[i].type == LESS)
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
