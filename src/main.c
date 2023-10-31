#include "../include/minishell.h"


void	ms_leaks(void)
{
	system("leaks -q minishell");
}

// [<] = open(filename, O_RDONLY);
// [>] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
// [>>] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)

char	*words[] = { "END", "PIPE", "LESS", "GREAT", "DLESS", "DGREAT", "WORD"};
char	*nodes[] = { "NODE_PIPE", "NODE_CMD", "NODE_REDIR"};

#define INFO(type, str) printf("[LINE]: %d | [%s]: %s\n", __LINE__, str, words[type])

typedef struct s_token
{
	enum e_type type;
	char	*lexeme;
	size_t	len;
} t_token;


t_token token_next(t_lexer *l);

typedef struct s_ast t_ast;
typedef struct s_pipe t_pipe;
typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;
typedef struct s_redir_item t_redir_item;

#if 1

struct s_pipe
{
	t_ast *left;
	t_ast *right;
};

struct s_cmd
{
	char	**argv;
	size_t 	cap;
	size_t	len;
	int		ms_close;
	t_redir *redir;
};


enum e_node_type
{
	NODE_PIPE,
	NODE_CMD,
	NODE_REDIR,
};

struct s_ast
{
	enum e_node_type type;
	union {
		t_pipe pipe;
		t_cmd cmd;
	};
};


void	add_item(t_cmd *cmd, char *item)
{
	if (cmd->cap == cmd->len)
	{
		cmd->cap *= 2;
		cmd->argv = ft_realloc(cmd->argv, sizeof(char *) * cmd->cap);
	}
	cmd->argv[cmd->len] = item;
	cmd->len += 1;
}
extern char **environ;

t_ast *command(t_lexer *lexer, t_token *token);

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


t_ast *cmd_node()
{
	t_ast *node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd.cap = 2;
	node->cmd.len = 0;
	node->cmd.ms_close = -1;
	node->cmd.argv = malloc(sizeof(char *) * node->cmd.cap);
	if (!node->cmd.argv)
		return (NULL);
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


t_ast *command(t_lexer *lexer, t_token *token)
{
	t_ast *node;

	node = cmd_node();
	while (token->type == WORD)
	{
		add_item(&node->cmd, token->lexeme);
		*token = token_next(lexer);
	}
	add_item(&node->cmd, NULL);
	return node;
}

t_ast *pipeline(t_lexer *lexer, t_token *token)
{
	if (token->type == PIPE)
	{
		ms_error("minishell: syntax error near unexpected token `|\'\n");
		return (NULL);
	}
	t_ast *left = command(lexer, token); // TODO: could pass left ast root of tree
	t_ast *node;

	if (token->type == PIPE)
	{
		*token = token_next(lexer);
		node = pipe_node(left, pipeline(lexer, token));
		return (node);
	}

	return (left);
}

int	ms_exec(t_ast *node, int *fd);

int	ms_exec_pipe(t_ast *node, int *fd)
{
	int	count = 0;
	int	pp[2];

	t_ast *l = node->pipe.left;
	t_ast *r = node->pipe.right;

	pipe(pp);



	int	lfd[2] = {
		fd[MS_STDIN],
		fd[MS_STDOUT],
	};

	lfd[MS_STDOUT] = pp[MS_STDOUT];
	l->cmd.ms_close = pp[MS_STDIN];

	count += ms_exec(l, lfd);

	int	rfd[2] = {
		fd[MS_STDIN],
		fd[MS_STDOUT],
	};


	rfd[MS_STDIN] = pp[MS_STDIN];
	r->cmd.ms_close = pp[MS_STDOUT];

	count += ms_exec(r, rfd);

	close(pp[MS_STDIN]);
	close(pp[MS_STDOUT]);
	return count;
}

int	ms_exec_cmd(t_ast *node, int *fd)
{
	t_cmd cmd = node->cmd;

	if (fork() == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);
		close(cmd.ms_close);

		char	*path = cmd.argv[0];
		ms_cmd_path(&path);
		
		if (execve(path, cmd.argv, environ) == -1)
		{
			ms_error("minishell: %s: command not found\n", cmd.argv[0]);
			exit(127);
		}
	}
	return (1);
}

int	ms_exec(t_ast *ast, int *fd)
{
	int	count;

	if (ast == NULL)
		return -1;

	if (ast->type == NODE_PIPE)
		count = ms_exec_pipe(ast, fd);
	if (ast->type == NODE_CMD)
		count = ms_exec_cmd(ast, fd);
	return count;
}

int	main()
{
// 	int	fd[2] = {
// 		MS_STDIN,
// 		MS_STDOUT,
// 	};

	while (1)
	{
		char	*line = readline("$> ");
		add_history(line);
		t_lexer lexer = ms_lexer_init(line);

		enum e_type type = ms_peek(&lexer);
		printf("[TOKEN]: %s\n", words[type]);

// 		t_token token = token_next(&lexer);
// 		t_ast *ast = pipeline(&lexer, &token);

// 		int count = ms_exec(ast, fd);
// 		for (int i = 0; i < count; i++)
// 			wait(NULL);
	}

	return 0;
}


t_lexer ms_lexer_init(char *line)
{
	t_lexer lexer;

	lexer.line = line;
	lexer.len = ft_strlen(line);
	lexer.pos = 0;
	return lexer;
}

enum e_type ms_peek(t_lexer *l)
{
	const char *tokens = "|<>";
	const size_t len = ft_strlen(tokens);
	size_t i;

	l->pos = ms_trim_left(l);
	i = 0;
	if (l->pos > l->pos) return END;
	if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<') return DLESS;
	if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '<') return DGREAT;
	while (i < len)
	{
		if (l->line[l->pos] == tokens[i])
			return i + PIPE;
		i += 1;
	}
	return WORD;
}



t_token token_next(t_lexer *l)
{
    size_t  len = 0;
// 	size_t	start;
    t_token token = {0};
    
    l->pos = ms_trim_left(l);

    if (l->pos > l->len) return token;

	// TODO: all tokens expect WORD could remove lexeme

    if (l->line[l->pos] == '|')
    {
        token.type = PIPE;
        token.lexeme = ft_substr(&l->line[l->pos], 0, 1);
        l->pos += 1;
        return token;
    }
    if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<')
    {
        token.type = DLESS;
        token.lexeme = ft_substr(&l->line[l->pos], 0, 2);
        l->pos += 2;
        return token;
    }
    if (l->line[l->pos] == '<')
    {
        token.type = LESS;
        token.lexeme = ft_substr(&l->line[l->pos], 0, 1);
        l->pos += 1;
        return token;
    }
    if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '>')
    {
        token.type = DGREAT;
        token.lexeme = ft_substr(&l->line[l->pos], 0, 2);
        l->pos += 2;
        return token;
    }
    if (l->line[l->pos] == '>')
    {
        token.type = GREAT;
        token.lexeme = ft_substr(&l->line[l->pos], 0, 1);
        l->pos += 1;
        return token;
    }
	// DOLLAR SIGN
	if (l->line[l->pos] == '\'' || l->line[l->pos] == '\"')
	{
		l->pos += 1;
		len = ms_consume(l, ms_isquote);
		token.len = len; // TODO: we dont need it
		token.type = WORD;
		token.lexeme = ft_substr(&l->line[l->pos], 0, len);
		l->pos += len + 1;
		return token;
	}
    if (l->pos < l->len)
    {
		len = ms_consume(l, ms_ismetachar);
		token.len = len;
        token.type = WORD;
        token.lexeme = ft_substr(&l->line[l->pos], 0, len);
        l->pos += len;
    }
    return token;
}

int	ms_isquote(int c)
{
	return c == '\'' || c == '\"';
}

int	ms_consume(t_lexer *l, int (*check)(int))
{
	size_t start = l->pos;
	size_t len = 0;

	while (start < l->len && !check(l->line[start]))
	{
		start += 1;
		len += 1;
	}
	return len;
}

#endif







#if 0



/* ================================================================================= */
#define PRINT(type, lexeme) printf("[TOKEN]: (%s) -> `%s`\n", words[type], lexeme);

int	exec_cmd(t_ast *cmd, int cls, int *fd)
{
	char	*cmmd = cmd->token.lexeme;
	char	*er = cmmd;

	pid_t pid = fork();

	if (pid == 0)
	{
		dup2(fd[MS_STDIN], MS_STDIN);
		dup2(fd[MS_STDOUT], MS_STDOUT);
		close(cls);

		char	*argv[] = {
			cmmd,
			NULL,
		};
		ms_cmd_path(&cmmd);
		if (execve(cmmd, argv, NULL) == -1) // need to pass envp
		{
			ms_error("minishell: %s: command not found\n", er);
			exit(127);
		}

	}
	return 1;
}

int	exec_pipe(t_ast *root, int cls, int *fd);

int	eval(t_ast *root, int cls, int *fd)
{
	int	count;

	if (root->token.type == PIPE) // call a function to handle pipe
	{
		count = exec_pipe(root, cls, fd);
	}
	if (root->token.type == WORD) // call a fnction to execute just one command
	{
		count = exec_cmd(root, cls, fd);
	}
	return count;
}



int	exec_pipe(t_ast *root, int cls, int *fd)
{
	int	count = 0;
	int	pp[2];



	fprintf(stderr, "fd[MS_STDIN]: %d\nfd[MS_STDOUT]: %d\n", fd[MS_STDIN], fd[MS_STDOUT]);
	pipe(pp);



	t_ast *left_node = root->left;
	t_ast *right_node = root->right;

	if (!left_node)
	{
		ms_error("minishell: syntax error near unexpected token `|\'\n");
		return -1;
	}

	int	lfd[2] = {
		fd[MS_STDIN],
		fd[MS_STDOUT],
	};
	int	lcls = cls;

	
	lfd[MS_STDOUT] = pp[MS_STDOUT];
	lcls = pp[MS_STDIN];

	count += eval(left_node, lcls, lfd);


	int	rfd[2] = {
		fd[MS_STDIN],
		fd[MS_STDOUT],
	};
	int	rcls = cls;

	rfd[MS_STDIN] = pp[MS_STDIN];
	rcls = pp[MS_STDOUT];



	count += eval(right_node, rcls, rfd);

	close(pp[MS_STDIN]);
	close(pp[MS_STDOUT]);


	return count;
}





#if 1
int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	char	*line;
	t_env	env;
	t_lexer	lexer;

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

	// prompt
	while (1)
	{
		line = readline("$> ");
		if (!line)
			return 0;
		add_history(line);
		lexer = ms_lexer_init(line);

		t_ast *root = parse(&lexer);

		post_order(root);

		int count = eval(root, cls, fd);

		for (int i = 0; i < count; i++)
			wait(NULL);


		free(line); // readline allocates memory
	}
	rl_clear_history(); // clear all memory for history
	return 0;
}
#endif


void	post_order(t_ast *root)
{
	if (root == NULL)
		return ;
	post_order(root->left);
	post_order(root->right);
	t_token token = root->token;
	PRINT(token.type, token.lexeme);
}


void	pre_order(t_ast *root)
{
	if (root == NULL)
		return ;
	t_token token = root->token;
	PRINT(token.type, token.lexeme);
	pre_order(root->left);
	pre_order(root->right);
}

t_ast *pipeline(t_lexer *lexer, t_token *token)
{
	t_ast *node = ast_node(*token);
	*token = token_next(lexer);

	while (token->type == PIPE)
	{
		if (token->type == PIPE)
		{
			t_ast *l = ast_node(*token);
			*token = token_next(lexer);
			t_ast *r = ast_node(*token);

			l->left = node;
			l->right = r;
			node = l;
		}
		*token = token_next(lexer);
	}
	return node;
}













t_ast *parse(t_lexer *lexer)
{
	t_token token = token_next(lexer);
	t_ast *root = pipeline(lexer, &token);
	

	return root;
}

#endif
