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

void	ms_prompt(t_env *env)
{
	const int	fd[2] = {MS_STDIN, MS_STDOUT};
	int	count;
	char	*line;
	t_ast	*ast;
	t_lexer	lexer;

	(void)env;


	while (1)
	{
		line = readline("$> ");
		if (!line)
			break ;
		lexer = ms_lexer_init(line);
		if (ms_peek(&lexer) == NEWLINE)
			continue;
		add_history(line);
		ast = ms_parse_pipe(&lexer);
		if (ast)
		{
			count = ms_exec(ast, (int*)fd);
			ms_wait(count);
		}
		ms_ast_destroy(ast);
		free(line);

	}
}

// TODO: fix redirs with pipeline
// TODO: fix || for pipeline

#if 1
int	main(int argc, char **argv, char **envp)
{
	atexit(ms_leaks);

	if (ms_interactive_mode())
		return (1);
	if (ms_catch_signal())
		return (1);

	env = ms_env_dup(envp);
	ms_prompt(&env);
	rl_clear_history();


	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}
#endif












