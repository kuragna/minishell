#include "../include/ms_exec.h"
#include "../include/ms_builtin.h"

#define LEFT	0
#define RIGHT	1


///TODO: make it safe, because we have buffer-overflow
struct s_fd_table
{
	int	fds[1024];
	size_t len;
};

struct s_fd_table table = {0};

void	ms_close(struct s_fd_table *table)
{
	size_t i;

	i = 0;
	while (i < table->len)
	{
		close(table->fds[i]);
		i += 1;
	}
	table->len = 0;
}

extern t_env env;
extern char	**ms_envp;
extern char	**environ; // just for test

int	exec_builtin_cmd(const t_args *args, int *fd)
{
	const char		*str = args->argv[0];
	const size_t	len = ft_strlen(str) + 1;
	int				status;

	status = 1;
	if (ft_memcmp(str, "cd", len) == 0)
	{
		status = ms_cd(&env, args->argv[1]);
	}
	if (ft_memcmp(str, "env", len) == 0)
	{
		status = ms_env(env);
	}
	if (ft_memcmp(str, "pwd", len) == 0)
	{
		status = ms_pwd();
	}
	if (ft_memcmp(str, "echo", len) == 0)
	{
		status = ms_echo(args->argv + 1, fd);
	}
	if (ft_memcmp(str, "export", len) == 0)
	{
		status = ms_export(&env, args->argv + 1);
	}
	if (ft_memcmp(str, "unset", len) == 0)
	{
		status = ms_unset(&env, args->argv + 1);
	}
	if (ft_memcmp(str, "exit", len) == 0)
	{
		ms_exit();
	}
	return status;
}


// TODO: built-in via pipeline
// TODO: built-in via redirs
#if 1
int	ms_exec_cmd(t_ast *node, int *fd)
{
	const t_cmd cmd = node->cmd;
	char	*path;
	char	*errmsg;

	ms_io_handle(&node->cmd.redirs, fd);

	if (!node->cmd.args.argv[0])
		return (-1);
	if (!exec_builtin_cmd(&cmd.args, fd))
		return (0);
	else if (fork() == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);
		ms_close(&table);

		path = cmd.args.argv[0];
		ms_cmd_path(&path);
		if (execve(path, cmd.args.argv, environ) == -1)
		{
			errmsg = strerror(errno);
			if (errno == 2)
				errmsg = "command not found";
			ms_error("minishell: %s: %s\n", cmd.args.argv[0], errmsg);
			exit(127);
		}
	}
	return (1);
}
#endif



int	ms_exec(t_ast *ast, int *fd)
{
	int	count;

	if (ast == NULL)
		return (-1);

	if (ast->type == NODE_PIPE)
	{
		count = ms_exec_pipe(ast, fd);
	}
	if (ast->type == NODE_CMD)
	{
		count = ms_exec_cmd(ast, fd);
	}
	return (count);
}

int	ms_exec_pipe(t_ast *node, int *fd)
{
	const t_ast	*nodes[2] = {node->pipe.left, node->pipe.right};
	int			count;
	int			pp[2];
	int			fd_[2];

	count = 0;
	if (pipe(pp) == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (-1);
	}
	table.fds[table.len++] = pp[MS_STDIN];
	table.fds[table.len++] = pp[MS_STDOUT];
	fd_[MS_STDIN] = fd[MS_STDIN];
	fd_[MS_STDOUT] = pp[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[LEFT], fd_);
	fd_[MS_STDIN] = pp[MS_STDIN];
	fd_[MS_STDOUT] = fd[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[RIGHT], fd_);
	// close all file descriptors in parent process
	ms_close(&table);
	return (count);
}
