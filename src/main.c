#include "../include/minishell.h"

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
	"QUOTE",
	"DQUOTE",
	"WORD"
};

extern char **environ;
char	**ms_envp;

t_array env;
t_array	ms_array_init()
{
	t_array	array;

	array.cap = 2;
	array.len = 0;
	array.items = malloc(sizeof(array.items) * array.cap);
	return (array);
}

void	ms_array_push(t_array *arr, void *item)
{
	if (arr->cap == arr->len)
	{
		arr->cap *= 2;
		arr->items = ft_realloc(arr->items, sizeof(arr->items) * arr->cap);
	}
	arr->items[arr->len] = item;
	arr->len += 1;
}



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



void	ms_prompt(t_array *env)
{
	int	fd[2];
	int	count;
	char	*line;
	t_ast	*ast;
	t_lexer	lexer;

	(void)env;
	(void)fd;
	(void)count;


	while (1)
	{
		line = readline("$> ");
		if (!line)
			break ;
		lexer = ms_lexer_init(line);
		fd[MS_STDIN] = MS_STDIN;
		fd[MS_STDOUT] = MS_STDOUT;

		//ast = ms_parse_pipe(&lexer);//ms_parse_and_or(&lexer);
		ast = ms_parse_and_or(&lexer);
		add_history(line);
		if (ast)
		{
			printf("[ROOT]: %s\n", nodes[ast->type]);
			printf("[LAST]: %s\n", words[ms_peek(&lexer)]);
			
			//ms_ast_print(ast);
			count = ms_exec(ast, (int*)fd);
			ms_wait(count);
		}
		ms_close(&table);
		//ms_ast_destroy(ast);
		free(line);

	}
}

// TODO: fix redirs with pipeline
// TODO: fix || for pipeline

#if 1
int	main(int argc, char **argv, char **envp)
{
	//atexit(ms_leaks);

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












