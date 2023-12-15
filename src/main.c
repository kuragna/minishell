/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:09:31 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/13 13:46:46 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_builtin.h"

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

int	g_status = 0;


// TODO: echo < $a -> "a doesnt exist"
// TODO: expansion within here-doc
// TODO: exit status if there syntax error -> 258
// TODO: exit status with different signal
// TODO: ctrl-c in here-doc need to exit
// TODO: free env at the end of program
// TODO: fix export z="a b" and then echo < $z which gives ambigious redirect as an error
// TODO: know why "echo" -> ctrl-c -> echo $? = 1

static void	ms_wait(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(-1, &g_status, 0);
		if (WIFEXITED(g_status))
		{
			g_status = WEXITSTATUS(g_status);
		}
		else if (!data->flag && WIFSIGNALED(g_status))
		{
			fprintf(stderr, "EXIT STATUS = %d\n", WEXITSTATUS(g_status));
			g_status = (WEXITSTATUS(g_status) + SIGINT);
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
	if (!ast)
		g_status = 258;
	if (ast)
	{
		count = ms_exec(ast, &l->data);
		if (count)
			ms_wait(&l->data, count);
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
