/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:09:31 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/04 14:15:32 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_builtin.h"

struct s_context	g_ctx;

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

char	*nodes[] = { "NODE_PIPE", "NODE_CMD", "NODE_AND", "NODE_OR"};
char	*words[] = {
	"NEWLINE",
	"PIPE", 
	"LESS", 
	"GREAT",
	"DLESS",
	"DGREAT",
	"AND",
	"OR",
	"DOLLAR",
	"WORD"
};

void	ms_table_add(struct s_fd_table *table, int fd)
{
	if (table->len == 1024)
		return ;
	if (fd > 2)
		table->fds[table->len++] = fd;
}

static void	ms_wait(int count)
{
	int	stat_log;
	int	i;

	i = 0;
	while (i < count)
	{
		wait(&stat_log);
		i += 1;
	}
}

static void	ms_prompt(void)
{
	int		fd[2];
	int		count;
	t_ast	*ast;
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
		if (!ms_peek(&lexer) || ms_check_quotes(lexer.line))
			continue ;
		add_history(lexer.line);
		fd[MS_STDIN] = MS_STDIN;
		fd[MS_STDOUT] = MS_STDOUT;
		ast = ms_parse_pipe(&lexer);
		if (ast)
			count = ms_exec(ast, fd);
		ms_wait(count);
		ms_ast_destroy(ast);
		ms_close(&g_ctx.table);
		free(lexer.line);
	}
}

#if 1
// TODO: fix sort env
// TODO: SIGV after unset
// TODO: fix export VAR
// TODO: fix ms_get_idx and ms_getenv
// TODO: fix builtin via pipeline
int	main(int argc, char **argv, char **envp)
{
	t_array	env;

	(void) argc, (void) argv;
	if (ms_interactive_mode())
		return (1);
	if (ms_catch_signal())
		return (1);
	env = ms_env_dup(envp);
	g_ctx.env = &env;
	ms_update_shlvl(g_ctx.env);
	ms_prompt();
	rl_clear_history();
	return (0);
}
#endif