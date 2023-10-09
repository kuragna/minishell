#include "../include/minishell.h"


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


void	ms_exit(char *line)
{
	if (!line || ft_strncmp(line, "exit", 4) == 0)
	{
		ft_putendl_fd("exit", MS_STDOUT);
		exit(EXIT_SUCCESS);
	}
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* name of environment variable should start with underscore */
int	ms_start(int c)
{
	return ft_isalpha(c) || c == '_';
}
/* name of environment variable should not contain special characters, except underscore */
int	ms_symbol(char *str, int c)
{
	while (*str && *str != c)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);	
		str += 1;
	}
	return (1);
}

/*
 *	'env' command prints variable if has [name=value]
 *	otherwise, just ignore
 *	Maybe good idea to add a flag to check if variable has both name and value or not
 * */
typedef struct s_env
{
	char	**vars;
	size_t	capacity;
	size_t	lenght;
} t_env;


// TODO: make it dynamicly
size_t	env_size(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i += 1;
	}
	return i;
}

void	env_realloc(t_env **env)
{
	size_t	i;
	char	**new;

	(*env)->capacity *= 2;
	new = malloc(sizeof(char *) * (*env)->capacity);

	i = 0;

	while (i < (*env)->lenght)
	{
		new[i] = (*env)->vars[i];
		i += 1;
	}

	free((*env)->vars);
	(*env)->vars = new;
}

void	env_append_null(t_env *env)
{
	env->vars[env->lenght] = NULL;	
}

void	env_add(t_env **env, char *var)
{
	if ((*env)->capacity == (*env)->lenght)
	{
		env_realloc(env);
	}
	(*env)->vars[(*env)->lenght] = var;
	if (var != NULL)
		(*env)->lenght += 1;
}

t_env env_dup(char **envp)
{
	size_t	i;
	t_env	env;

	i = 0;

	env.capacity = env_size(envp);
	env.lenght = 0;
	env.vars = malloc(sizeof(char *) * (env.capacity + 1));

	while (envp[i] != NULL)
	{
		env.vars[i] = envp[i];
		i += 1;
	}
	env.lenght += i;
	return env;
}

void	env_sort(t_env *env)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*t;

	i = 0;
	while (env->vars[i])
	{
		j = 0;
		while (env->vars[j])
		{
			len = ft_strlen(env->vars[j]);
			if (ft_strncmp(env->vars[i], env->vars[j], len) < 0)
			{
				t = env->vars[i];
				env->vars[i] = env->vars[j];
				env->vars[j] = t;
			}
			j += 1;
		}
		i += 1;
	}
}


void	export_print(t_env *env)
{
	size_t	i;

	i = 0;
	env_sort(env);
	while (env->vars[i])
	{
		printf("declare -x %s\n", env->vars[i]);
		i += 1;
	}
}

void	ms_export(t_env *env, char *var)
{
	char	*end;
	int		i;
	int		len;

	if (!ms_start(*var) || !ms_symbol(var + 1, '='))
	{
		MS_ERROR("export: ", var, ": not a valid identifier");
		return ;
	}
	end = ft_strchr(var, '=');
	i = env->lenght - 1;

	if (!end)
		return ;

	len = end - var;
	while (i >= 0)
	{
		if (ft_strncmp(env->vars[i], var, len) == 0)
		{
			env->vars[i] = var;
			return ;
		}
		i -= 1;
	}
	env_add(&env, var);
	env_append_null(env);
}

void	ms_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->lenght && env->vars[i])
	{
		printf("%s\n", env->vars[i]);
		i += 1;
	}
}

void	ms_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	write(MS_STDOUT, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ms_catch_signal()
{
	int	err;
	struct sigaction sa;

	sa.sa_handler = ms_sig_handler;
	sa.sa_flags = SA_RESTART;
	err = sigaction(SIGINT, &sa, NULL); // ctrl-c
	if (err == -1)
	{
		MS_ERROR("minishell: ", "", strerror(errno));
		return (1);
	}
	err = sigaction(SIGQUIT, &sa, NULL); // ctrl-/
	if (err == -1)
	{
		MS_ERROR("minishell: ", "", strerror(errno));
		return (1);
	}
	return (0);
}

int	ms_terminal_mode(void)
{
	struct termios attr;

	// TODO: make sure error format as follow [minishell: res: err]
	if (!isatty(MS_STDIN))
	{
		MS_ERROR("minishell: ", ttyname(MS_STDIN), strerror(errno));
		return (1);
	}
	if (tcgetattr(MS_STDIN, &attr) == -1)
	{
		MS_ERROR("minishell: ", "", strerror(errno));
		return (1);
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(MS_STDIN, TCSANOW, &attr) == -1)
	{
		MS_ERROR("minishell: ", "", strerror(errno));
		return (1);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	atexit(ms_leaks);

	(void) argc;
	(void) argv;
	(void) envp;

	char	*line;

	if (ms_terminal_mode())
		return (1);
	// catch signal
	if (ms_catch_signal())
		return (1);


	// prompt
	while (1)
	{
		line = readline("$ ");
		ms_exit(line); // check before call function
		add_history(line);
		free(line); // readline allocates memory
	}
	rl_clear_history(); // clear all memory for history
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