#include "../include/ms_parser.h"
#include "../include/ms_builtin.h"
#include "../libft/libft.h"

#include <assert.h>

extern char	*words[];
extern t_array env;

int	ms_parse_args(t_cmd *cmd, t_lexer *lexer)
{
	char	*arg;

	if (cmd->args.items== NULL)
		return (1);
	while (ms_peek(lexer) == WORD)
	{
		arg = ms_get_word(lexer);
		ms_array_append(&cmd->args, arg);
	}
	return (0);
}

int	ms_parse_files(struct s_redirs *ptr, t_lexer *lexer)
{
	t_token_type	type;

	if (ptr->items == NULL)
		return (1);
	while (1)
	{
		type = ms_peek(lexer);
		if (!(type >= LESS && type <= DGREAT))
			break ;
		ms_token_next(lexer);
		if (ms_peek(lexer) != WORD)
		{
			PERR(":%s:%d\n", __FUNCTION__, __LINE__);
			ms_expected_token(ms_peek(lexer));
			return (1);
		}
		ms_redir_add(ptr, ms_get_word(lexer), type);
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
	if (!(type >= LESS && type <= DGREAT))
	{
		ms_array_append(&node->cmd.args, NULL);
		return (node);
	}
	node->cmd.redirs = ms_redirs_init();
	while (1)
	{
		type = ms_peek(lexer);
		if (!(type >= LESS && type <= DGREAT))
			break ;
		if (ms_parse_files(&node->cmd.redirs, lexer))
		{
			PERR(":%s:%d\n", __FUNCTION__, __LINE__);
			//ms_ast_destroy(node);
			return (NULL);
		}
		if (ms_parse_args(&node->cmd, lexer))
		{
			PERR(":%s:%d\n", __FUNCTION__, __LINE__);
			//ms_ast_destroy(node);
			return (NULL);
		}
		ms_parse_args(&node->cmd, lexer);
	}
	ms_array_append(&node->cmd.args, NULL);
	return (node);
}

t_ast	*ms_parse_and_or(t_lexer *lexer)
{
	t_ast	*left;
	t_ast	*right;
	t_token_type type;
	t_ast_node	ast_node;

	type = ms_peek(lexer);
	if (type == AND || type == OR)
	{
		ms_expected_token(type);
		return (NULL);
	}
	left = ms_parse_pipe(lexer);
	if (!left) return (NULL);
	type = ms_peek(lexer);
	if (type == AND || type == OR)
	{
		ast_node = NODE_AND;
		if (type != AND)
			ast_node = NODE_OR;
		ms_token_next(lexer);
		if (ms_peek(lexer) != WORD)
		{
			ms_expected_token(ms_peek(lexer));
			return (NULL);
		}
		right = ms_and_or_node(ast_node, left, ms_parse_and_or(lexer));
		return (right);
	}
	return (left);
}

// TODO: fix double free in error case

t_ast *ms_parse_pipe(t_lexer *lexer)
{
	t_ast *left;
	t_ast *right;

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
			//ms_ast_destroy(left);
			return (NULL);
		}
		right = ms_pipe_node(left, ms_parse_pipe(lexer));
		if (!right)
		{
			//ms_ast_destroy(left);
			return (NULL);
		}
		return (right);
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





void	ms_redir_add(t_redirs *ptr, char *path, t_token_type type)
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

t_redirs ms_redirs_init()
{
	t_redirs items;

	items.cap = 2;
	items.len = 0;
	items.items = malloc(sizeof(*items.items) * items.cap);
	return (items);
}

char	*ms_get_word(t_lexer *lexer)
{
	t_token_type type = ms_peek(lexer);
	char *word = ms_token_next(lexer).lexeme;
	PERR("[LEXEME]: %s, [TYPE]: %s\n", word, words[type]);
	return (word);
}
