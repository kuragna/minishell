/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:09:31 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/07 18:21:21 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_builtin.h"

struct s_context	g_ctx;

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

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
			g_ctx.exit_status = WEXITSTATUS(stat_log);
		}
		if (WIFSIGNALED(stat_log))
		{
			g_ctx.exit_status = (128 + SIGINT);
		}
		i += 1;
	}
}

static void	ms_prompt_(t_lexer *l)
{
	int		fd[2];
	int		count;
	t_ast	*ast;

	add_history(l->line);
	fd[MS_STDIN] = MS_STDIN;
	fd[MS_STDOUT] = MS_STDOUT;
	ast = ms_parse_pipe(l);
	if (ast)
	{
		count = ms_exec(ast, fd);
		if (count)
			ms_wait(count);
		ms_ast_destroy(ast);
		ms_close(&g_ctx.table);
	}
	free(l->line);
}

static void	ms_prompt(void)
{
	t_lexer	lexer;

	while (1)
	{
		lexer.line = readline("$> ");
		if (!lexer.line)
		{
			printf("exit\n");
			break ;
		}
		lexer = ms_lexer_init(lexer.line);
		if (!ms_peek(&lexer))
		{
			free(lexer.line);
			g_ctx.exit_status = 0;
			continue ;
		}
		if (ms_check_quotes(lexer.line))
		{
			free(lexer.line);
			g_ctx.exit_status = 1;
			continue ;
		}
		ms_prompt_(&lexer);
	}
}

#if 1
// TODO: exit status 1 with Ctrl-c
// TODO: cd if directory doesnt exist any more
// TODO: make sure that memory free it
int	main(int argc, char **argv, char **envp)
{
	t_array	env;

	(void) argc, (void) argv;
	if (ms_interactive_mode())
		return (1);
	if (ms_signal())
		return (1);
	env = ms_env_dup(envp);
	g_ctx.env = &env;
	ms_update_shlvl();
	ms_prompt();
	ms_array_append(g_ctx.env, NULL);
	ft_free(g_ctx.env->items);
	rl_clear_history();
	atexit(ms_leaks);
	return (0);
}
#endif