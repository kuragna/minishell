#include "../include/minishell.h"

/*
	COMMAND: echo hello $USER1 $USER2 > file | cat -e file | grep h

		            	  __ PIPELINE __
                     ___/                \____
                   /                           \
            __ PIPELINE __                   COMMAND
	      /                \                    |
       COMMAND           COMMAND               ARGS
      /        \             |                  | 
   ARGS       REDIR        ARGS               0: grep
     |          |            |                1: h
   0: echo      >         0: cat
   1: $USER1 	|	  	  1: -e
   2: $USER2 file         2: file		
*/

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

// [<] = open(filename, O_RDONLY);
// [>] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
// [>>] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)

char	*nodes[] = { "NODE_PIPE", "NODE_CMD"};

char	*words[] = {
	"END",
	"PIPE", 
	"LESS", 
	"GREAT",
	"DOLLAR",
	"QUOTE",
	"DQUOTE",
	"DLESS", 
	"DGREAT", 
	"WORD"
};

void	ms_arg_push(t_cmd *cmd, char *arg)
{
	t_args *args = &cmd->args;
	if (args->cap == args->len)
	{
		args->cap *= 2;
		args->argv = ft_realloc(args->argv, sizeof(args->argv) * args->cap);
	}
	
	args->argv[args->len] = arg;
	args->len += 1;
}

extern char **environ;

t_ast *command(t_lexer *lexer);

t_env env;

t_args ms_args_init()
{
	t_args args;

	args.cap = 2;
	args.len = 0;
	args.argv = malloc(sizeof(args.argv) * args.cap);
	return (args);
}


t_ast *cmd_node()
{
	t_ast 	*node;
	t_cmd	cmd;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	cmd.args = ms_args_init();
	ft_memset(&cmd.redirs, 0, sizeof(cmd.redirs));
	node->type = NODE_CMD;
	node->cmd = cmd;
	return (node);
}
t_ast *pipe_node(t_ast *left, t_ast *right)
{
	t_ast *node;
	
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->pipe.left = left;
	node->pipe.right = right;
	return (node);
}


// TODO: fix DOLLAR sign
t_ast *command(t_lexer *lexer)
{
	t_ast			*node;
	char			*str;
	t_token_type	type;

	type = ms_peek(lexer);
	if (type == END)
		return (NULL);
	node = cmd_node(); // TODO: check for NULL
	while (type == WORD || type == DOLLAR || type == QUOTE)
	{
		str = ms_token_next(lexer).lexeme;
		if (type == DOLLAR)
			str = ms_getenv(&env, str + 1);
		if (str)
			ms_arg_push(&node->cmd, str);
		type = ms_peek(lexer);
	}
	ms_arg_push(&node->cmd, NULL);
	return node;
}

t_ast *pipeline(t_lexer *lexer)
{
	t_ast	*left;
	t_ast	*node;

	if (ms_peek(lexer) == PIPE)
	{
		ms_error("minishell: syntax error near unexpected token `|\'\n");
		return (NULL);
	}
	left = command(lexer); // TODO: could pass left ast root of tree
	if (ms_peek(lexer) == PIPE)
	{
		ms_token_next(lexer);
		node = pipe_node(left, pipeline(lexer));
		return (node);
	}
	return (left);
}

int	ms_exec(t_ast *node, int *fd, int cls);

int	ms_exec_pipe(t_ast *node, int *fd, int cls)
{
	int	count;
	int	pp[2];


	count = 0;
	t_ast *l = node->pipe.left;
	t_ast *r = node->pipe.right;

	if (pipe(pp) == -1)
	{
		ms_error("minishell: %s\n", strerror(errno));
		return (-1);
	}

	int	lfd[2] = { fd[MS_STDIN], fd[MS_STDOUT] };
	int	lcls = cls;

	lfd[MS_STDOUT] = pp[MS_STDOUT];
	lcls = pp[MS_STDIN];
	count += ms_exec(l, lfd, lcls);

	int	rfd[2] = { fd[MS_STDIN], fd[MS_STDOUT] };
	int	rcls = cls;

	rfd[MS_STDIN] = pp[MS_STDIN];
	rcls = pp[MS_STDOUT];


	count += ms_exec(r, rfd, rcls);

	close(pp[MS_STDIN]);
	close(pp[MS_STDOUT]);
	return count;
}


int	exec_builtin_cmd(const t_args *args)
{
	const char		*str = args->argv[0];
	const size_t	len = ft_strlen(str) + 1;
	int				status;

	status = 1;
	if (ft_memcmp(str, "cd", len) == 0)
	{
		status = ms_cd(&env, args->argv[1]);
	}
	if (ft_memcmp(str, "env", len) == 0)
	{
		status = ms_env(env);
	}
	if (ft_memcmp(str, "pwd", len) == 0)
	{
		status = ms_pwd();
	}
	if (ft_memcmp(str, "echo", len) == 0)
	{
		status = ms_echo(args->argv + 1);
	}
	if (ft_memcmp(str, "export", len) == 0)
	{
		status = ms_export(&env, args->argv + 1);
	}
	if (ft_memcmp(str, "unset", len) == 0)
	{
		status = ms_unset(&env, args->argv + 1);
	}
	if (ft_memcmp(str, "exit", len) == 0)
		ms_exit();
	return status;
}

char	**ms_envp;




int	ms_exec_cmd(t_ast *node, int *fd, int cls)
{
	const t_cmd cmd = node->cmd;
	char	*path;

	if (cmd.args.argv[0] == NULL) // 
		return (-1);

	// TODO: fix built-in via pipeline
	if (!exec_builtin_cmd(&cmd.args))
		return 0;
	else if (fork() == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);
		close(cls);

		path = cmd.args.argv[0];
		ms_cmd_path(&path);
		if (execve(path, cmd.args.argv, ms_envp) == -1)
		{
			ms_error("minishell: %s: command not found\n", cmd.args.argv[0]);
			exit(127);
		}
	}
	return (1);
}

int	ms_exec(t_ast *ast, int *fd, int cls)
{
	int	count;

	if (ast == NULL)
		return (-1);

	if (ast->type == NODE_PIPE)
		count = ms_exec_pipe(ast, fd, cls);
	if (ast->type == NODE_CMD)
		count = ms_exec_cmd(ast, fd, cls);
	return (count);
}



// TODO: should not execute built-in command via pipeline
// TODO: check for multi input of [|, >, <, $]
// TODO: make sure for all signals
#if 0
int main(int argc, char **argv, char **envp)
{
	//atexit(ms_leaks);
	(void) argc;
	(void) argv;

	char	*line;
	t_lexer	lexer;
	t_ast	*ast;

	if (ms_interactive_mode())
		return (1);
	if (ms_catch_signal())
		return (1);
	env = env_dup(envp);


	int	fd[2] = {
		MS_STDIN,
		MS_STDOUT,
	};
	int	cls = -1;
	(void) cls;
	(void) fd;
	// prompt
	while (1)
	{
		line = readline("$> ");
		if (!line || !*line)
		{
			ft_putendl_fd("exit", MS_STDOUT);
			break ;
		}

		add_history(line);
		lexer = ms_lexer_init(line);

		ast = pipeline(&lexer);



		ms_envp = ms_envcpy(&env); // TODO: could we need to free it every time?

		int count = ms_exec(ast, fd, cls);
		for (int i = 0; i < count; i++)
			wait(NULL);



		//ms_ast_destroy(ast);
		//free(ms_envp);
		(void) ast;
		free(line); // readline allocates memory
	}
	rl_clear_history(); // clear all memory for history
	return (0);
}

#endif

#if 1

t_redir *redir_node(const char *filename, t_token_type type)
{
	t_redir *node;
	
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->type = type;
	return (node);
}

struct s_redirs ms_redirs_init()
{
	struct s_redirs items;

	items.cap = 2;
	items.len = 0;
	items.items = malloc(sizeof(*items.items) * items.cap); // TODO: check NULL
	return (items);
}

char	*ms_get_word(t_lexer *lexer)
{
	// TODO: here expand all words
	t_token_type type = ms_peek(lexer);
	char *word = ms_token_next(lexer).lexeme;
	printf("[LEXEME]: %s, [TYPE]: %s\n", word, words[type]);
	return (word);
}

void	redir_push(struct s_redirs *ptr, char *filename, t_token_type type)
{
	t_redir item;

	item.filename = filename;
	item.type = type;
	if (ptr->cap == ptr->len)
	{
		ptr->cap *= 2;
		ptr->items = ft_realloc(ptr->items, sizeof(*ptr->items) * ptr->cap);
	}
	ptr->items[ptr->len] = item;
	ptr->len += 1;
}

void	parse_args(t_cmd *cmd, t_lexer *lexer)
{
	char	*arg;

	while (ms_peek(lexer) == WORD)
	{
		arg = ms_get_word(lexer);
		ms_arg_push(cmd, arg);
	}
}

int	parse_files(struct s_redirs *self, t_lexer *lexer)
{
	t_token_type type;

	type = ms_peek(lexer);
	while (1)
	{
		if (type == PIPE || type == WORD || type == END)
			break ;
		ms_token_next(lexer);
		PRINT_LINE("TOKEN", words[type]);
		if (ms_peek(lexer) != WORD)
		{
			ms_error("minishell: %s `newline\'\n", SYNT_ERR);
			return (1);
		}
		PRINT_LINE("TOKEN", words[type]);
		redir_push(self, ms_get_word(lexer), type);
		type = ms_peek(lexer);
	}
	return (0);
}


t_ast *parse_cmd(t_lexer *lexer)
{
	t_ast *node;

	node = cmd_node();
	if (!node)
		return (NULL);
	parse_args(&node->cmd, lexer);
	return (node);
}





t_ast *parse_redir(t_lexer *lexer)
{
	t_ast *node;
	t_token_type type;

	node = parse_cmd(lexer);
	type = ms_peek(lexer);
	if (type == PIPE || type == WORD || type == END)
	{
		ms_arg_push(&node->cmd, NULL);
		return (node);
	}
	//type = ms_peek(lexer); // TODO: Test this
	node->cmd.redirs = ms_redirs_init();
// 	type = ms_peek(lexer);
// 	while (1)
// 	{
// 		if (type == PIPE || type == WORD || type == END)
// 			break ;
// 		ms_token_next(lexer);
// 		printf("LINE: %d -> [TOKEN]: %s\n", __LINE__, words[type]);
// 		if (ms_peek(lexer) != WORD)
// 		{
// 			ms_error("minishell: %s `newline\'\n", SYNT_ERR);
// 			return (NULL);
// 		}
// 		printf("LINE: %d -> [TOKEN]: %s\n", __LINE__, words[type]);
// 		redir_push(&node->cmd.redirs, ms_get_word(lexer), type);
// 		type = ms_peek(lexer);
// 	}
	PRINT_LINE("LAST", words[ms_peek(lexer)]);
	parse_args(&node->cmd, lexer);
	ms_arg_push(&node->cmd, NULL);
	return (node);
}


t_ast *parse_pipe(t_lexer *lexer)
{
	t_ast *left;
	t_ast *node;

	if (ms_peek(lexer) == PIPE)
	{
		ms_error("minishell: %s `|\'\n", SYNT_ERR);
		return (NULL);
	}

	left = parse_redir(lexer);

	if (!left)
		return (NULL);

	if (ms_peek(lexer) == PIPE)
	{
		ms_token_next(lexer);
		node = pipe_node(left, parse_pipe(lexer));
		return (node);
	}
	return (left);
}

// TODO: fix there is no space between tokens

int	main()
{
	int	fd[2];
	while (1)
	{
		char	*line = readline("$> ");
		if (!line)
			continue;
		t_lexer lexer = ms_lexer_init(line);

		fd[MS_STDIN] = MS_STDIN;
		fd[MS_STDOUT] = MS_STDOUT;

		t_ast *ast = parse_pipe(&lexer);

		if (ast)
		{
			printf("[NODE]: %s\n", nodes[ast->type]);
			ms_ast_print(ast);
		}

		//exec_test(ast, fd);


		(void) ast;
		add_history(line);
	}
	return 0;
}

#endif
