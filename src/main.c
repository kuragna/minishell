#include "../include/minishell.h"

void	ms_leaks(void)
{
	system("leaks -q minishell");
}

/* ================ parsing ================= */
/* TODO: < redirect input
 * TODO: > redirect output
 * TODO: << 
 * TODO: >> redirect output in append mode
 * TODO: | pipe
 * TODO: $ environment variable
 * TODO: cmd
 * TODO: cmd args */
/* ================ parsing ================= */

/* ================ builtin ================= */
/* TODO: echo with -n
 * DONE: cd "relative or absolute path"
 * TODO: export
 * TODO: unset
 * TODO: env
 * DONE: pwd
 * DONE: exit */
/* ================ builtin ================= */
/* ================ interactive mode ================= */
/* TODO: ctrl-c: kill child process
 * DONE: ctrl-c: displays a new prompt
 * DONE: ctrl-D: exit
 * TODO: ctrl-\ does nothin */
/* ================ interactive mode ================= */


// [<] = open(filename, O_RDONLY);
// [>] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
// [>>] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)

char	*words[] = { "END", "PIPE", "LESS", "GREAT", "DLESS", "DGREAT", "WORD"};


int	ms_error(const char *fmt, ...)
{
	va_list ap;
	char	*str;

	va_start(ap, fmt);

	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt += 1;
			if (*fmt == 's')
			{
				str = va_arg(ap, char *);
				ft_putstr_fd(str, MS_STDERR);
				fmt += 1;
			}
		}
		write(MS_STDERR, fmt, 1);
		fmt += 1;
	}
	va_end(ap);
	return 1;
}

enum e_type
{
	END, // end of input
	PIPE, // pipe
	LESS, // redirect input
	GREAT, // redirect output
	DLESS, // redirect input with delimitar
	DGREAT, // redirect outut in append mode
	WORD, // command name and filename
};
typedef struct
{
	char *line;
	size_t len;
	size_t	pos;
} t_lexer;


typedef struct s_token
{
	enum e_type type;
	char	*lexeme;
	size_t	len;
} t_token;




typedef struct s_ast t_ast;

struct s_ast
{
	t_token token;
	t_ast *left;
	t_ast *right;
};

t_ast *parser(t_lexer *lexer);
void	pre_order(t_ast *root);
void	post_order(t_ast *root);


t_ast *ast_node(t_token token)
{
	t_ast *node = malloc(sizeof(*node));
	if (!node)
		return NULL;
	node->left = NULL;
	node->token = token;
	node->right = NULL;
	return node;
}



int ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return l->pos;
}

int ms_ismetachar(int c)
{
    if (ft_isspace(c) || c == '|' || c == '>' || c == '<')
        return 1;
    return 0;
}

t_lexer ms_lexer_init(char *line, size_t len)
{
	t_lexer lexer;

	lexer.line = line;
	lexer.len = len;
	lexer.pos = 0;
	return lexer;
}



t_token token_next(t_lexer *l)
{
    size_t  len = 0;
    t_token token = {0};
    
    l->pos = ms_trim_left(l);

    if (l->pos > l->len) return token;

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
    if (l->pos < l->len)
    {
        size_t start = l->pos;
        while (start < l->len && !ms_ismetachar(l->line[start]))
        {
            start += 1;
            len += 1;
        }
		token.len = len;
        token.type = WORD;
        token.lexeme = ft_substr(&l->line[l->pos], 0, len);
        l->pos += len;
    }

    return token;
}







/* ================================================================================= */
#define PRINT(type, lexeme) printf("[TOKEN]: (%s) -> `%s`\n", words[type], lexeme);

int	exec_cmd(t_ast *cmd, int cls, int *fd)
{
	char	*cmmd = cmd->token.lexeme;
	char	*er = cmmd;

	pid_t pid = fork();

	if (pid == 0)
	{
// 		fprintf(stderr, "\n\n[CMD]: %s [STDIN: %d, STDOUT: %d]\n\n", er, fd[MS_STDIN], fd[MS_STDOUT]);

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
	int	count = 0;
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


#define INFO() printf("[LINE]: %d, [FUNCTION]: %s\n", __LINE__, __FUNCTION__)

int	test = 0;

int	exec_pipe(t_ast *root, int cls, int *fd)
{
	int	count = 0;
	int	pp[2];


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
	int	cls = 1;

	// prompt
	while (1)
	{
		line = readline("$> ");
		if (!line)
			return 0;
		add_history(line);
		lexer = ms_lexer_init(line, ft_strlen(line));

		t_ast *root = parser(&lexer);

	
		//post_order(root);



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

t_ast *parser(t_lexer *lexer)
{
	t_token token = token_next(lexer);
	t_ast *root = pipeline(lexer, &token);
	return root;
}