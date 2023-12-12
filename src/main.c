/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:09:31 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/12 13:15:28 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_builtin.h"

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

int	g_status = 0;

static void	ms_wait(int count)
{
	int	stat_log;
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(-1, &stat_log, 0);
		if (WIFEXITED(stat_log))
		{
			g_status = WEXITSTATUS(stat_log);
		}
		if (WIFSIGNALED(stat_log))
		{
			g_status = (128 + SIGINT);
		}
		i += 1;
	}
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
	l->data.fd[MS_STDIN] = MS_STDIN;
	l->data.fd[MS_STDOUT] = MS_STDOUT;
	ast = ms_parse_pipe(l);
	if (ast)
	{
		count = ms_exec(ast, &l->data);
		if (count)
			ms_wait(count);
		ms_ast_destroy(ast);
		ms_close(&l->data.table);
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
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_array	env;
	t_data	data;

	(void) argc, (void) argv;
	ft_memset(&data, 0, sizeof(data));
	if (ms_interactive_mode())
		return (1);
	if (ms_signal())
		return (1);
	env = ms_env_dup(envp);
	ms_update_shlvl(&env);
	data.env = &env;
	ms_prompt(&data);
	rl_clear_history();
	return (0);
}
