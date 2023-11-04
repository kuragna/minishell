#ifndef MS_PARSE_H
#define MS_PARSE_H

#include "../include/ms_lexer.h"

typedef struct s_ast t_ast;
typedef struct s_pipe t_pipe;
typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;
typedef struct s_args t_args;

enum e_node_type
{
	NODE_PIPE,
	NODE_CMD,
};

struct s_redir
{
	t_token_type 	type;
	const char		*filename;
};

struct s_redirs
{
	t_redir	*items;
	size_t	cap;
	size_t	len;
};

struct s_pipe
{
	t_ast *left;
	t_ast *right;
};

struct s_args
{
	char	**argv;
	size_t	len;
	size_t	cap;
};


struct s_cmd
{
	t_args args;
	struct s_redirs redirs;
};

struct s_ast
{
	enum e_node_type type;
	union {
		t_pipe pipe;
		t_cmd cmd;
	};
};

#endif //MS_PARSE_H
