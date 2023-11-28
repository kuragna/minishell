#include "../include/minishell.h"
#include "../include/ms_builtin.h"

struct s_fd_table table = {0};

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

t_array env;

void	ms_table_add(struct s_fd_table *table, int fd)
{
	if (table->len == 1024)
		return ;
	if (fd > 2)
		table->fds[table->len++] = fd;
}

void	ms_wait(int count)
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

void	ms_prompt()
{
	int	fd[2];
	int	count;
	t_ast	*ast;
	t_lexer	lexer;

	(void) env;
	(void) fd;
	(void) count;
	(void) ast;


	while (1)
	{
		lexer.line = readline("$> ");
		if (!lexer.line)
		{
			printf("exit\n");
			break ;
		}
		lexer = ms_lexer_init(lexer.line);
		lexer.env = &env;
		if (!ms_peek(&lexer) || ms_check_quotes(lexer.line))
			continue ;
		add_history(lexer.line);

#if 0
		t_token_type type = ms_peek(&lexer);
		while (type != NEWLINE)
		{
			char	*lexeme = ms_token_next(&lexer).lexeme;
			printf("[TOKEN]: %s | [LEXEME]: %s\n", words[type], lexeme);
			type = ms_peek(&lexer);
		}
	


		continue ;
#endif

		fd[MS_STDIN] = MS_STDIN;
		fd[MS_STDOUT] = MS_STDOUT;

		//ast = ms_parse_and_or(&lexer);
		ast = ms_parse_pipe(&lexer);
		ms_array_append(&env, NULL);
		if (ast)
		{
			count = ms_exec(ast, fd);
			ms_wait(count);
		}
		ms_ast_destroy(ast);
		ms_close(&table);
		free(lexer.line);
	}
}


#if 1
// DONE: fix export
// DONE: fix $LS2
// DONE: update shell level
// TODO: fix export VAR
// TODO: fix ms_get_idx and ms_getenv
// TODO: fix builtin via pipeline
// TODO: change realloc but make sure function copies sizeof() * len
int	main(int argc, char **argv, char **envp)
{
	//atexit(ms_leaks);

	if (ms_interactive_mode())
		return (1);
// 	if (ms_catch_signal())
// 		return (1);
	
	env = ms_env_dup(envp);
	ms_update_shlvl(&env);
	ms_prompt();
	rl_clear_history();


	return (0);
	(void)argc;
	(void)argv;
	(void)envp;
}
#endif