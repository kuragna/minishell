#include "../include/minishell.h"

#include <unistd.h>

#define MS_PRINT(str) printf("%s:%d: %s\n", __FILE__, __LINE__, str)

/* ================ parsing ================= */
/* TODO: trim space
 * TODO: < redirect input
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
 * TODO: cd "relative or absolute path"
 * TODO: pwd
 * TODO: export
 * TODO: unset
 * TODO: env
 * TODO: exit */
/* ================ builtin ================= */
/* ================ interactive mode ================= */
/* TODO: ctrl-C: displays a new prompt
 * TODO: ctrl-D: exit
 * TODO: ctrl-\ does nothin */
/* ================ interactive mode ================= */


// [<] = open(filename, O_RDONLY);
// [>] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
// [>>] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)

char	*tokens[] = {
	"end of input",
	"pipe",
	"less",
	"great",
	"dless",
	"dgreat",
	"word",
	"arg",
};

void	ms_error(const int size, ...)
{
	va_list	ap;

	va_start(ap, size);
	for (int i = 0; i < size; i++)
	{
		ft_putstr_fd(va_arg(ap, char *), 2);
	}
	ft_putchar_fd('\n', 2);
	va_end(ap);
}


typedef enum
{
	TOKEN_END = 0, // end of input
	TOKEN_PIPE, // pipe
	TOKEN_LESS, // redirect input
	TOKEN_GREAT, // redirect output
	TOKEN_DLESS, // redirect input with delimitar
	TOKEN_DGREAT, // redirect outut in append mode
	TOKEN_WORD, // command name and filename
	TOKEN_ARG,
} t_token_type;
typedef struct
{
	char *line;
	size_t len;
	size_t	pos;
	size_t	start;
	size_t	end;
} t_lexer;

typedef struct s_token
{
	t_token_type token_type;
	char	*text;
	size_t	len;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char	*name;
	char	**args;
} t_cmd;

int ms_trim_left(t_lexer *l)
{
	while (l->pos < l->len && ft_isspace(l->line[l->pos]))
	{
		l->pos += 1;
	}
	return l->pos;
}

t_cmd	*cmd_new(t_token *token)
{
	if (token->token_type != TOKEN_WORD)
		return NULL;
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));

	cmd->name = malloc(sizeof(*cmd) * (token->len + 1));

	ft_strlcpy(cmd->name, token->text, token->len + 1);

	return cmd;
}

int	ms_is_metachar(int c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

t_lexer ms_lexer_init(char *line, size_t len)
{
	t_lexer lexer;

	lexer.line = line;
	lexer.len = len;
	lexer.pos = 0;
	lexer.end = 0;
	return lexer;
}

void	token_(t_token *token, t_token_type type, t_lexer *l, size_t len)
{
	token->token_type = type;
	token->len = len;
	l->pos += len;
}

t_token token_next(t_lexer *l)
{
	l->pos = ms_trim_left(l);

	t_token token = {
		.token_type = TOKEN_END,
		.text = l->line + l->pos,
	};

	if (l->pos >= l->len) return token;

	if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<')
	{
		token_(&token, TOKEN_DLESS, l, 2);
	}
	else if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '>')
	{
		token_(&token, TOKEN_DGREAT, l, 2);
	}
	else if (l->line[l->pos] == '|')
	{
		token_(&token, TOKEN_PIPE, l, 1);
	}
	else if (l->line[l->pos] == '<')
	{
		token_(&token, TOKEN_LESS, l, 1);
	}
	else if (l->line[l->pos] == '>')
	{
		token_(&token, TOKEN_GREAT, l, 1);
	}
	else
	{
		while (l->pos < l->len && !ms_is_metachar(l->line[l->pos]))
		{
			l->pos += 1;
			token.len += 1;
		}
		token.token_type = TOKEN_WORD;
	}
	return token;
}


void	ms_sig_handler(int sig)
{
	(void) sig;
	printf("Not implemented yet\n");
	return ;
}

void	ms_exit(char *line)
{
	if (!line || ft_strncmp(line, "exit", 4) == 0)
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct s_env
{
	t_list	*list;
	size_t	size;
} t_env;

void	ms_env_sort(t_list *list)
{
	char	*t;
	size_t	len;

	while (list)
	{
		t_list	*next = list->next;
		while (next)
		{
			len = ft_strlen(list->content);
			if (ft_strncmp(list->content, next->content, len) > 0)
			{
				// TODO: swap function
				t = list->content;
				list->content = next->content;
				next->content = t;
			}
			next = next->next;
		}
		list = list->next;
	}
}




void	ms_env(t_env *env)
{
	size_t	i;
	t_list	*list;

	i = 0;
	list = env->list;
	while (list && i < env->size)
	{
		ft_printf("%s\n", list->content);
		list = list->next;
		i += 1;
	}
}


void	ms_env_dup(t_env *env, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&env->list, ft_lstnew(envp[i]));
		env->size += 1;
		i += 1;
	}
}

void	ms_export_print(t_env *env)
{
	size_t	i;
	t_list	*list;

	i = 0;
	list = env->list;
	ms_env_sort(env->list);
	// TODO: ignore last one, same with export
	while (list && i < env->size)
	{
		ft_printf("declare -x %s\n", list->content);
		list = list->next;
		i += 1;
	}
}


int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	if (!isatty(MS_STDIN))
	{
		MS_ERROR("minishell: ", "Invalid tty", "");
		return (1);
	}

	t_env env = {0};

	ms_env_dup(&env, envp);

	ms_env(&env);



	return 0;

	signal(SIGINT, ms_sig_handler);

	while (1)
	{
		// TODO: if cmd builtin just invoke function
		// TODO: otherwise, create child process
		char	*line = readline("ms$ ");
		ms_exit(line);
	}

	return 0;
}


/*
 * redirection = {
 * 	'>' <word>
 * 	'>' <word>
 * 	'>>' <word>
 * 	'<<' <word>
 * }
 * simple_cmd = {
 *	<word>
 * }
 *
*/

/*
	input-> lexer-> tokens
	tokens-> parser-> AST
	AST->	evaluator-> evaluated AST
	evaluated AST -executor-> output
*/
/*
 * input line 					| 	valid/invalid
 * cat								Valid
 * cat file1 	 				|	Valid
 * cat < file1 					|	Valid
 * cat > file1					|	Valid
 * cat < file1 > file2			|	Valid
 * cat > file1 < file2			|	Valid
 * cat file1 > file2			|	Valid
 * cat > file2 file1			|	Valid
 * < file1						|	Invalid
 * cat file1 <					| 	Invalid
 * cat file1 >					|	Invalid
 * cat file1 > file2 > file3 	|	Invalid
 * cat < file1 < file2			|	Invalid
 */