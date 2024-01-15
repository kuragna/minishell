/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:45:48 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/15 14:37:25 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_exec.h"
#include "../include/ms_builtin.h"

#include <stdio.h>

extern int	g_status;

int	ms_exec_in(t_data *data, pid_t *last_pid)
{
	int				status;
	size_t			i;
	const char		*str = *data->argv;
	const size_t	len = ft_strlen(str) + 1;
	const t_builtin	cmds[MS_SIZE] = {
	{"echo", ms_echo}, {"cd", ms_cd}, {"pwd", ms_pwd},	{"export", ms_export},
	{"unset", ms_unset}, {"env", ms_env}, {"exit", ms_exit}};

	i = -1;
	status = -1;
	while (++i < MS_SIZE)
	{
		if (ft_strncmp(str, cmds[i].name, len) == 0)
		{
			status = cmds[i].exec(data);
			break ;
		}
	}
	*last_pid = -1;
	g_status = status;
	return (status);
}

static int	ms_fork(t_data *data, char **argv, pid_t *pid)
{
	char	*path;
	char	**envp;

	*pid = fork();
	if (*pid == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (1);
	}
	if (*pid == 0)
	{
		dup2(data->fd[MS_STDIN], MS_STDIN);
		dup2(data->fd[MS_STDOUT], MS_STDOUT);
		ms_close(&data->table);
		path = *argv;
		ms_cmd_path(data->env, &path);
		envp = ms_envcpy(data->env);
		if (execve(path, argv, envp) == -1)
		{
			free(envp);
			ms_error_exec(*argv);
		}
	}
	return (0);
}

int	ms_exec_cmd(t_ast *node, t_data *data, pid_t *last)
{
	t_cmd	cmd;

	cmd = node->cmd;
	data->argv = cmd.args.items;
	if (data->heredoc_flag)
		return (0);
	if (ms_io_handle(&cmd.redirs, data))
		return (0);
	if (cmd.args.len <= 1 || !*cmd.args.items)
		return (0);
	if (ms_exec_in(data, last) != -1)
		return (0);
	if (ms_fork(data, cmd.args.items, last))
		return (0);
	return (1);
}

int	ms_exec(t_ast *ast, t_data *data, pid_t *last)
{
	int	count;

	if (ast == NULL)
		return (0);
	if (ast->type == NODE_PIPE)
	{
		data->pipe_flag = 1;
		count = ms_exec_pipe(ast, data, last);
	}
	if (ast->type == NODE_CMD)
	{
		count = ms_exec_cmd(ast, data, last);
	}
	return (count);
}

int	ms_exec_pipe(t_ast *node, t_data *data, pid_t *last)
{
	const t_ast	*nodes[2] = {node->pipe.left, node->pipe.right};
	int			count;
	int			pp[2];
	t_data		_data;

	count = 0;
	if (pipe(pp) == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (-1);
	}
	ms_table_add(&data->table, pp[MS_STDIN]);
	ms_table_add(&data->table, pp[MS_STDOUT]);
	_data = *data;
	_data.fd[MS_STDIN] = data->fd[MS_STDIN];
	_data.fd[MS_STDOUT] = pp[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[MS_LEFT], &_data, last);
	_data.fd[MS_STDIN] = pp[MS_STDIN];
	_data.fd[MS_STDOUT] = data->fd[MS_STDOUT];
	count += ms_exec((t_ast *)nodes[MS_RIGHT], &_data, last);
	ms_close(&data->table);
	return (count);
}
