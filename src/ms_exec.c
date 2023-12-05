/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:45:48 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 19:50:46 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_exec.h"
#include "../include/ms_builtin.h"

int	ms_exec_in(t_array args, int *fd)
{
	const char		*str = ms_str_tolower(*args.items);
	const size_t	len = ft_strlen(str) + 1;
	const t_builtin	cmds[] = {
	{"echo", ms_echo},	{"cd", ms_cd}, {"pwd", ms_pwd},	{"export", ms_export},
	{"unset", ms_unset}, {"env", ms_env}, {"exit", ms_exit}};
	int				status;
	size_t			i;

	i = -1;
	status = -1;
	g_ctx.items = args.items + 1;
	while (++i < MS_SIZE)
	{
		if (ft_strncmp(str, cmds[i].name, len) == 0)
		{
			status = cmds[i].run(fd);
			break ;
		}
	}
	return (status);
}

int	ms_fork(char **argv, int *fd)
{
	char	*path;
	char	**envp;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (1);
	}
	if (pid == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);
		ms_close(&g_ctx.table);
		path = *argv;
		ms_cmd_path(&path);
		envp = ms_envcpy(g_ctx.env);
		if (execve(path, argv, envp) == -1)
		{
			free(envp);
			ms_exec_error(*argv);
		}
	}
	return (0);
}

int	ms_exec_cmd(t_ast *node, int *fd)
{
	t_cmd	cmd;

	cmd = node->cmd;
	if (ms_io_handle(&cmd.redirs, fd))
		return (0);
	if (cmd.args.len <= 1 || !*cmd.args.items)
		return (0);
	if (ms_exec_in(cmd.args, fd) != -1)
		return (0);
	else if (ms_fork(cmd.args.items, fd))
		return (0);
	return (1);
}

int	ms_exec(t_ast *ast, int *fd)
{
	int	count;

	if (ast == NULL)
		return (0);
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
	int			_fd[2];

	count = 0;
	if (pipe(pp) == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (-1);
	}
	ms_table_add(&g_ctx.table, pp[MS_STDIN]);
	ms_table_add(&g_ctx.table, pp[MS_STDOUT]);
	_fd[MS_STDIN] = fd[MS_STDIN];
	_fd[MS_STDOUT] = pp[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[LEFT], _fd);
	_fd[MS_STDIN] = pp[MS_STDIN];
	_fd[MS_STDOUT] = fd[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[RIGHT], _fd);
	ms_close(&g_ctx.table);
	return (count);
}
