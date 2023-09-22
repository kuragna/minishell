#include "../include/minishell.h"

#include <unistd.h>



/* ================ parsing ================= */
/* TODO: trim space
 * TODO: < redirect input
 * TODO: > redirect output
 * TODO: << 
 * TODO: >> redirect output in append mode
 * TODO: | pipe
 * TODO: $ environment variable
 * TODO: cmd */
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

/* ls --> simple cmd
 * ls -l --> cmd with option
 * ls | grep --> pipe cmd
 * < file cmd --> redirect input file
 * cmd > file --> redirect output
 **/

typedef enum 
{
	TOKEN_PIPE,
	TOKEN_R_IN,
	TOKEN_R_APPEND,
	TOKEN_R_OUT,
	TOKEN_OTHER,
} Token_type;

typedef struct Token
{
	Token_type	token_type;
	char	*lexeme;
	struct Token *next;
} Token;

Token *token_node(char *lexeme, Token_type token_type)
{
	Token *token = malloc(sizeof(*token));
	token->token_type = token_type;
	token->lexeme = lexeme;
	token->next = NULL;
	return token;
}

void	token_add(Token **list, Token *token)
{
	token->next = *list;
	*list = token;
}

void	print_token(Token *list)
{
	const char	*tokens[] = {
		"TOKEN_PIPE",
		"TOKEN_R_IN",
		"TOKEN_R_APPEND",
		"TOKEN_R_OUT",
		"TOKEN_OTHER",
	};
	while (list)
	{
		printf("[%s]: %s\n", tokens[list->token_type], list->lexeme);
		list = list->next;
	}
}

int main2(void)
{
	Token	*list = NULL;
	char	*input = "< infile ls | cat > outfile >> file";
	char	**token = ft_split(input, ' ');

	int	i = 0;
	while (token[i] != NULL)
	{
		if (ft_strncmp(token[i], ">>", 2) == 0)
		{
			token_add(&list, token_node(token[i], TOKEN_R_APPEND));
		}
		else if (ft_strncmp(token[i], "<", 1) == 0)
		{
			token_add(&list, token_node(token[i], TOKEN_R_IN));
		}
		else if (ft_strncmp(token[i], "|", 1) == 0)
		{
			token_add(&list, token_node(token[i], TOKEN_PIPE));
		}
		else if (ft_strncmp(token[i], ">", 1) == 0)
		{
			token_add(&list, token_node(token[i], TOKEN_R_OUT));
		}
		else
			token_add(&list, token_node(token[i], TOKEN_OTHER));
		i += 1;
	}
	print_token(list);
	return (0);
}

// 	rl_replace_line(NULL, 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	add_history(NULL);

void	find_leaks(void)
{
	system("leaks -q minishell");
}


void	ms_error(const char *res, const char *strerr)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)res, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)strerr, 2);
}




char	*ms_trim_left(char *line)
{
	while (*line && ft_isspace(*line))
	{
		line += 1;
	}
	return (line);
}

void	ms_readline()
{
	char	*prompt = ft_strjoin("ms - ", getcwd(NULL, 0)); // NOTE: this is just for test changing path
	while (1)
	{
		char	*line = readline(ft_strjoin(prompt, "$"));

		// TODO: replace line with token
		if (ft_memcmp(line, "exit", ft_strlen(line)) == 0)
			exit(EXIT_SUCCESS);
		if (ft_memcmp(line, "echo", 4) == 0)
			ms_echo(line);
		if (ft_memcmp(line, "env", 3) == 0)
			ms_env();
		if (ft_memcmp(line, "pwd", 3) == 0)
			ms_pwd();
		add_history(line); // NOTE: try [UP] or [DOWN] key
	}
	rl_clear_history(); // NOTE: reset memory for history
}

void	ms_echo(char *str)
{
	// NOTE: not tested enough
	// TODO: handle trim space
	// TODO: fix strign if has quotes function printing newline
	// TODO: with option -n
	// TODO: trim space from right
	
	str += 4;
	str = ms_trim_left(str);

	printf("%s\n", str);

	while (*str != '\0')
	{
		printf("[%d] - [%c]\n", *str, *str);
		str += 1;
	}

	return ;
	while (*str != '\0')
	{
		if (*str == MS_SLASH)
			str += 1;
		if (*(str - 1) != MS_SLASH)
		{
			if (*str == MS_S_QUOTE || *str == MS_D_QUOTE)
				str += 1;
		}
		ft_printf("%c", *str);
		str += 1;
	}
	ft_printf("\n");
}


int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;


	ms_readline();

	return (0);
}
