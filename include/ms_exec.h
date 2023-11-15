#ifndef MS_EXEC
#define MS_EXEC

#include <errno.h>
#include <string.h>

#include "./ms_parser.h"

#define MS_STDIN	0
#define	MS_STDOUT	1

// TODO: make sure that doesnt have buffer-overflow
struct s_fd_table
{
	int		fds[1024];
	size_t	len;
};

int	exec_builtin_cmd(t_array *args, int *fd);
int	ms_io_handle(t_redirs *ptr, int *fd);
int	ms_cmd_path(char **cmd);
int	ms_error(const char *fmt, ...);

int	ms_exec_or(t_ast *node, int *fd);
int	ms_exec_and(t_ast *node, int *fd);
int	ms_exec_pipe(t_ast *node, int *fd);
int	ms_exec_cmd(t_ast *node, int *fd);
int	ms_exec(t_ast *ast, int *fd);

int	ms_here_doc(const char *path);
int	ms_open(const char *path, int oflag, int mode);

#endif //MS_EXEC

