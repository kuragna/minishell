#include "../include/ms_exec.h"
#include "../include/ms_builtin.h"

#define LEFT	0
#define RIGHT	1

int	exit_status;
extern char *nodes[];

// TODO: fix error message in empty quotes case


extern struct s_fd_table table;

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


extern t_array env;
extern char	**ms_envp;
extern char	**environ; // just for test

int	exec_builtin_cmd(t_array *args, int *fd)
{
	const char		*str = args->items[0];
	const size_t	len = ft_strlen(str) + 1;
	int				status;

	status = 1;
	if (ft_memcmp(str, "cd", len) == 0)
	{
		status = ms_cd(&env, args->items[1]);
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
		status = ms_echo(args->items + 1, fd);
	}
	if (ft_memcmp(str, "export", len) == 0)
	{
		status = ms_export(&env, args->items + 1);
	}
	if (ft_memcmp(str, "unset", len) == 0)
	{
		status = ms_unset(&env, args->items + 1);
	}
	if (ft_memcmp(str, "exit", len) == 0)
	{
		ms_exit();
	}
	return status;
}

void	ms_test(const char *cmd)
{
	int	exit_status;
	char	*str;

	exit_status = 127;
	str = "command not found";
	if (errno != 2)
	{
		str = strerror(errno);
		exit_status = 126;
	}
	ms_error("minishell: %s: %s\n", cmd, str);
	exit(exit_status);
}


int	ms_exec_cmd(t_ast *node, int *fd)
{
	const t_cmd cmd = node->cmd;
	char	*path;

	if (ms_io_handle(&node->cmd.redirs, fd))
		return (0);
	if (!node->cmd.args.items[0])
	{
		return (0);
	}
	if (!exec_builtin_cmd((t_array*)&cmd.args, fd))
		return (0);
	else if (fork() == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);

// 		PERR("stdin: %d | stdout: %d\n", fd[MS_STDIN], fd[MS_STDOUT]);


		ms_close(&table);
		path = cmd.args.items[0];
		ms_cmd_path(&path);
		if (execve(path, cmd.args.items, environ) == -1)
		{
			ms_test(cmd.args.items[0]);
		}
	}
	return (1);
}


int	ms_exec(t_ast *ast, int *fd)
{
	int	count;

	if (ast == NULL)
		return (0);
	if (ast->type == NODE_AND)
	{
		count = ms_exec_and(ast, fd);
	}
	if (ast->type == NODE_OR)
	{
		count = ms_exec_or(ast, fd);
	}
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

int	ms_exec_and(t_ast *ast, int *fd)
{
	(void) ast;
	(void) fd;

	PERR(":%s:%s:%d -> `Not impelemented yet`\n",
			__FILE__,
			__FUNCTION__,
			__LINE__);
	exit(1);
	return 0;
}

int	ms_exec_or(t_ast *ast, int *fd)
{
	int	stat_log;
	int	count = 0;

	t_ast	*left = ast->and_or.left;
	t_ast	*right = ast->and_or.right;

	count += ms_exec(left, fd);
	wait(&stat_log);

	// case1: exit_status is zero
	// case2: exit_status is non-zero

	if (WEXITSTATUS(stat_log) == 0)
	{
		return (count);
	}
	count += ms_exec(right, fd);

	return (count);
}

int	ms_exec_pipe(t_ast *node, int *fd)
{
	const t_ast	*nodes[2] = {node->pipe.left, node->pipe.right};
	int			count;
	int			pp[2];
	int			_fd[2];

	count = 0;
	if (pipe(pp) == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (-1);
	}
	ms_table_add(&table, pp[MS_STDIN]);
	ms_table_add(&table, pp[MS_STDOUT]);
	_fd[MS_STDIN] = fd[MS_STDIN];
	_fd[MS_STDOUT] = pp[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[LEFT], _fd);
	_fd[MS_STDIN] = pp[MS_STDIN];
	_fd[MS_STDOUT] = fd[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[RIGHT], _fd);
	ms_close(&table);
	return (count);
}

int	ms_io_handle(struct s_redirs *ptr, int *fd)
{
	char	*path;
	size_t i;
	int	in;
	int	out;

	i = 0;
	in = -1;
	out = -1;
	while (i < ptr->len)
	{
		path = ptr->items[i].path;
		if (ptr->items[i].type == DLESS)
		{
			in = ms_here_doc(path);
			if (in == -1)
				return (1);
			fd[MS_STDIN] = in;
		}
		if (ptr->items[i].type == LESS)
		{
			in = ms_open(path, O_RDONLY, 0);
			if (in == -1)
				return (1);
			fd[MS_STDIN] = in;
		}
		if (ptr->items[i].type == GREAT)
		{

			out = ms_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out == -1)
				return (1);
			fd[MS_STDOUT] = out;
		}
		if (ptr->items[i].type == DGREAT)
		{
			out = ms_open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out == -1)
				return (1);
			fd[MS_STDOUT] = out;
		}
		ms_table_add(&table, in);
		ms_table_add(&table, out);
		i += 1;
	}
	return (0);
}


