
#include "../include/minishell.h"

static int	ms_open(const char *path, int oflag, int mode)
{
	int	fd;

	fd = open(path, oflag, mode);
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

	fd = ms_open(dlmtr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (line && *line && ft_strncmp(line, dlmtr, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	ms_io_handle(struct s_redirs *ptr, int *fd)
{
	char	*path;
	size_t i;
	int	fd_;

	fd_ = -2;
	i = 0;
	while (i < ptr->len)
	{
		path = (char*)ptr->items[i].path;
		if (ptr->items[i].type == DLESS)
		{
			if (!ms_here_doc(path))
				fd_ = ms_open(path, O_RDONLY, 0);
			unlink(path);
			fd[MS_STDIN] = fd_;
		}
		if (ptr->items[i].type == LESS)
		{
			fd_ = ms_open(path, O_RDONLY, 0);
			fd[MS_STDIN] = fd_;
		}
		if (ptr->items[i].type == GREAT)
		{
			fd_ = ms_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fd[MS_STDOUT] = fd_;
		}
		if (ptr->items[i].type == DGREAT)
		{
			fd_ = ms_open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			fd[MS_STDOUT] = fd_;
		}
		i += 1;
	}
	return (0);
}
