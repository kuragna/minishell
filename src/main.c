#include "../include/minishell.h"

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

char	*nodes[] = { "NODE_PIPE", "NODE_CMD"};
char	*words[] = {
	"NEWLINE",
	"PIPE", 
	"LESS", 
	"GREAT",
	"DLESS",
	"DGREAT",
	"DOLLAR",
	"QUOTE",
	"DQUOTE",
	"WORD"
};

extern char **environ;
char	**ms_envp;
t_env env;

#if 1


void	ms_wait(int count)
{
	int	status;
	int	i;

	i = 0;
	while (i < count)
	{
		wait(&status);
		i += 1;
	}
}

// TODO: fix redirs with pipeline
// TODO: fix || for pipeline

int	main(int argc, char **argv, char **envp)
{
	atexit(ms_leaks);
	t_ast *ast;
	int	count;
	int	fd[2] = { MS_STDIN, MS_STDOUT};

	if (ms_interactive_mode())
		return (1);
	if (ms_catch_signal())
		return (1);

// 	env = ms_env_dup(envp);

	while (1)
	{
		char	*line = readline("$> ");
		if (!line)
			break ;
		t_lexer lexer = ms_lexer_init(line);
		add_history(line);
		if (ms_peek(&lexer) == NEWLINE)
			continue;

		fd[MS_STDIN] = MS_STDIN;
		fd[MS_STDOUT] = MS_STDOUT;
		
		ast = ms_parse_pipe(&lexer);
		if (ast)
		{
			count = ms_exec(ast, fd);
			ms_wait(count);
		}
		ms_ast_destroy(ast);
		free(line);
	}
	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}
#endif
