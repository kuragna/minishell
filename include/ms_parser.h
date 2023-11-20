/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:44:02 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/20 16:56:55 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H

# include <stdio.h>
# include "../libft/libft.h"
# include "./ms_lexer.h"
# include "./ms_malloc.h"

# define PERR(...) fprintf(stderr, __VA_ARGS__)

typedef struct s_ast	t_ast;
typedef struct s_pipe	t_pipe;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_and_or	t_and_or;
typedef struct s_redirs	t_redirs;

typedef enum e_ast_node
{
	NODE_PIPE = 0,
	NODE_CMD,
	NODE_AND,
	NODE_OR,
}	t_ast_node;


struct s_redir
{
	t_token_type	type;
	char			*path;
};

struct s_redirs
{
	t_redir	*items;
	size_t	cap;
	size_t	len;
};

struct s_cmd
{
	t_array		args;
	t_redirs	redirs;
};

struct s_pipe
{
	t_ast	*left;
	t_ast	*right;
};
struct s_and_or
{
	t_ast	*left;
	t_ast	*right;
};

struct s_ast
{
	t_ast_node	type;
	union {
		t_and_or	and_or;
		t_pipe		pipe;
		t_cmd		cmd;
	};
};

t_ast		*ms_and_or_node(t_ast_node node_type, t_ast *left, t_ast *right);
t_redir		*ms_redir_node(char *path, t_token_type type);
t_ast		*ms_pipe_node(t_ast *left, t_ast *right);
t_ast		*ms_cmd_node(void);
t_redirs	ms_redirs_init(void);
char		*ms_get_word(t_lexer *lexer);
t_array		ms_array_init(void);
void		ms_redir_add(t_redirs *ptr, char *path, t_token_type type);
t_ast		*ms_parse_and_or(t_lexer *lexer);
t_ast		*ms_parse_pipe(t_lexer *lexer);
t_ast		*ms_parse_cmd(t_lexer *lexer);
t_ast		*ms_parse_redir(t_lexer *lexer);
int			ms_parse_args(t_cmd *cmd, t_lexer *lexer);
int			ms_parse_files(t_redirs *ptr, t_lexer *lexer);
void		ms_ast_destroy(t_ast *ast);

#endif //MS_PARSER_H
