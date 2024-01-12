/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:09:31 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/12 15:38:40 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_builtin.h"

int	g_status = 0;

static void	ms_wait(int pipe_flag, int count, pid_t last_pid)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (i < count)
	{
		pid = waitpid(-1, &status, 0);
		if (last_pid != -1 && pid == last_pid && WIFEXITED(status))
		{
			g_status = WEXITSTATUS(status);
		}
		else if (!pipe_flag && WIFSIGNALED(status))
		{
			g_status += 128;
		}
		i += 1;
	}
}

static void	ms_lexer_set(t_lexer *l)
{
	l->data.fd[MS_STDIN] = MS_STDIN;
	l->data.fd[MS_STDOUT] = MS_STDOUT;
	l->data.quotes_flag = 0;
	l->data.heredoc_flag = 0;
	l->data.pipe_flag = 0;
	l->data.pid = -1;
}

static void	ms_prompt_(t_lexer *l)
{
	int		count;
	t_ast	*ast;

	if (ms_check_quotes(l->line))
	{
		free(l->line);
		g_status = 1;
		return ;
	}
	add_history(l->line);
	ms_lexer_set(l);
	ast = ms_parse_pipe(l);
	if (!ast)
		g_status = 258;
	if (ast)
	{
		count = ms_exec(ast, &l->data, &l->data.pid);
		if (count)
			ms_wait(l->data.pipe_flag, count, l->data.pid);
		ms_close(&l->data.table);
		ms_ast_destroy(ast);
	}
	free(l->line);
}

static void	ms_prompt(t_data *data)
{
	t_lexer	l;

	l.data = *data;
	while (1)
	{
		l.line = readline("$> ");
		if (!l.line)
		{
			printf("exit\n");
			break ;
		}
		ms_lexer_init(&l, l.line);
		if (!ms_peek(&l))
		{
			free(l.line);
			g_status = 0;
			continue ;
		}
		ms_prompt_(&l);
		l.data.heredoc_flag = 1;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_array	env;
	t_data	data;

	(void) argc, (void) argv;
	ft_memset(&data, 0, sizeof(data));
	ms_interactive_mode();
	if (ms_signal())
		return (1);
	env = ms_env_dup(envp);
	ms_update_shlvl(&env);
	data.env = &env;
	ms_prompt(&data);
	ms_array_append(&env, NULL);
	ft_free(env.items);
	rl_clear_history();
	return (0);
}
