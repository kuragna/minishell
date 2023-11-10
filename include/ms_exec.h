#ifndef MS_EXEC
#define MS_EXEC

#include <errno.h>
#include <string.h>
#include "../include/ms_parser.h"
#include "../include/ms_malloc.h"

#define MS_STDIN	0
#define	MS_STDOUT	1


int	exec_builtin_cmd(const t_args *args);
int	ms_exec_cmd(t_ast *node, int *fd);
int	ms_io_handle(struct s_redirs *ptr, int *fd);
int	ms_cmd_path(char **cmd);
int	ms_error(const char *fmt, ...);
int	ms_exec_pipe(t_ast *node, int *fd);
int	ms_exec(t_ast *ast, int *fd);

#endif //MS_EXEC

