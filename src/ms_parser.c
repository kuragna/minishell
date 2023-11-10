#include "../include/ms_parser.h"
#include "../include/ms_builtin.h"
#include "../libft/libft.h"

extern char	*words[];
extern t_env env;

int	ms_parse_args(t_cmd *cmd, t_lexer *lexer)
{
	char	*arg;

	if (cmd->args.argv == NULL)
		return (1);
	while (ms_peek(lexer) == WORD)
	{
		arg = ms_get_word(lexer);
		ms_arg_push(cmd, arg);
	}
	return (0);
}

int	ms_parse_files(struct s_redirs *ptr, t_lexer *lexer)
{
	t_token_type	type;

	if (ptr->items == NULL)
		return (1);
	type = ms_peek(lexer);
	while (1)
	{
		if (type == PIPE || type == WORD || type == NEWLINE)
			break ;
		ms_token_next(lexer);
		if (ms_peek(lexer) != WORD)
		{
			PERR(":%s:%d\n", __FUNCTION__, __LINE__);
			ms_expected_token(ms_peek(lexer));
			return (1);
		}
		ms_redir_push(ptr, ms_get_word(lexer), type);
		type = ms_peek(lexer);
	}
	return (0);
}

t_ast *ms_parse_redir(t_lexer *lexer)
{
	t_ast *node;
	t_token_type type;

	node = ms_parse_cmd(lexer);
	if (!node)
		return (NULL);
	type = ms_peek(lexer);
	if (type == PIPE || type == WORD || type == NEWLINE)
	{
		ms_arg_push(&node->cmd, NULL);
		return (node);
	}
	node->cmd.redirs = ms_redirs_init();
	while (1)
	{
		type = ms_peek(lexer);
		if (type == PIPE || type == NEWLINE)
			break ;
		if (ms_parse_files(&node->cmd.redirs, lexer))
		{
			ms_ast_destroy(node);
			return (NULL);
		}
		if (ms_parse_args(&node->cmd, lexer))
		{
			ms_ast_destroy(node);
			return (NULL);
		}
		ms_parse_args(&node->cmd, lexer);
	}
	ms_arg_push(&node->cmd, NULL);
	return (node);
}

t_ast *ms_parse_pipe(t_lexer *lexer)
{
	t_ast *left;
	t_ast *node;

	if (ms_peek(lexer) == PIPE)
	{
		ms_expected_token(ms_peek(lexer));
		return (NULL);
	}

	left = ms_parse_redir(lexer);

	if (!left)
		return (NULL);

	if (ms_peek(lexer) == PIPE)
	{
		ms_token_next(lexer);
		if (ms_peek(lexer) == NEWLINE)
		{
			ms_expected_token(ms_peek(lexer));
			ms_ast_destroy(left);
			return (NULL);
		}
		node = ms_pipe_node(left, ms_parse_pipe(lexer));
		if (!node)
		{
			ms_ast_destroy(left);
			return (NULL);
		}
		return (node);
	}
	return (left);
}

t_ast *ms_parse_cmd(t_lexer *lexer)
{
	t_ast *node;

	node = ms_cmd_node();
	if (node)
		ms_parse_args(&node->cmd, lexer);
	return (node);
}

t_args ms_args_init()
{
	t_args args;

	args.cap = 2;
	args.len = 0;
	args.argv = malloc(sizeof(args.argv) * args.cap);
	return (args);
}


t_ast *ms_cmd_node()
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

t_ast *ms_pipe_node(t_ast *left, t_ast *right)
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

void	ms_redir_push(struct s_redirs *ptr, char *path, t_token_type type)
{
	t_redir item;

	item.path = path;
	item.type = type;
	if (ptr->cap == ptr->len)
	{
		ptr->cap *= 2;
		ptr->items = ft_realloc(ptr->items, sizeof(*ptr->items) * ptr->cap);
	}
	ptr->items[ptr->len] = item;
	ptr->len += 1;
}

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

t_redir *ms_redir_node(char *path, t_token_type type)
{
	t_redir *node;
	
	node = malloc(sizeof(*node));
	if (node)
	{
		node->path = path;
		node->type = type;
	}
	return (node);
}

struct s_redirs ms_redirs_init()
{
	struct s_redirs items;

	items.cap = 2;
	items.len = 0;
	items.items = malloc(sizeof(*items.items) * items.cap);
	return (items);
}

char	*ms_get_word(t_lexer *lexer)
{
	t_token_type type = ms_peek(lexer);
	char	*dollar;
	char *word = ms_token_next(lexer).lexeme;

	if (*word == '$')
	{
		PERR("here: %s\n", word);
		// TODO: replace getenv by ms_getenv
		dollar = getenv(word + 1);
		return (dollar);
	}
	PERR("[LEXEME]: %s, [TYPE]: %s\n", word, words[type]);
	return (word);
}
