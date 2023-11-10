#ifndef MS_PARSE_H
#define MS_PARSE_H

#include <stdio.h>
#include "../include/ms_lexer.h"
#include "../include/ms_malloc.h"
#define PERR(...) fprintf(stderr, __VA_ARGS__)


typedef struct s_ast t_ast;
typedef struct s_pipe t_pipe;
typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;
typedef struct s_args t_args;

enum e_ast_node
{
	NODE_PIPE,
	NODE_CMD,
};

struct s_redir
{
	t_token_type 	type;
	char			*path;
};

struct s_redirs
{
	t_redir	*items;
	size_t	cap;
	size_t	len;
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

struct s_pipe
{
	t_ast *left;
	t_ast *right;
};

struct s_ast
{
	enum e_ast_node type;
	union {
		t_pipe pipe;
		t_cmd cmd;
	};
};

struct s_redirs	ms_redirs_init();
t_redir	*ms_redir_node(char *path, t_token_type type);
t_ast	*ms_cmd_node();
t_ast	*ms_pipe_node(t_ast *left, t_ast *right);

void	ms_redir_push(struct s_redirs *ptr, char *path, t_token_type type);
void	ms_arg_push(t_cmd *cmd, char *arg);
char	*ms_get_word(t_lexer *lexer);
int		ms_parse_args(t_cmd *cmd, t_lexer *lexer);
int		ms_parse_files(struct s_redirs *ptr, t_lexer *lexer);
void	ms_ast_destroy(t_ast *ast);


t_ast	*ms_parse_redir(t_lexer *lexer);
t_ast 	*ms_parse_pipe(t_lexer *lexer);
t_ast	*ms_parse_cmd(t_lexer *lexer);

#endif //MS_PARSE_H
