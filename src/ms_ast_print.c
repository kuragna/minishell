#include "../include/minishell.h"

//#include "main.c"

extern char *words[];
void	ms_ast_print(t_ast *ast);

void	pipe_print(t_ast *ast)
{
	if (!ast)
		return ;
	printf("\nNODE_PIPE:\n");
	ms_ast_print(ast->pipe.left);
	ms_ast_print(ast->pipe.right);
}

void	and_print(t_ast *ast)
{
	if (!ast)
		return ;
	printf("\nNODE_AND:\n");
	ms_ast_print(ast->and_or.left);
	ms_ast_print(ast->and_or.right);
}

void	or_print(t_ast *ast)
{
	if (!ast)
		return ;
	printf("\nNODE_OR:\n");
	ms_ast_print(ast->and_or.left);
	ms_ast_print(ast->and_or.right);
}

void	ms_ast_print(t_ast *ast)
{
	if (!ast) return ;
	if (ast->type == NODE_CMD) 	cmd_print(&ast->cmd);
	if (ast->type == NODE_AND) 	and_print(ast);
	if (ast->type == NODE_OR)	or_print(ast);
	if (ast->type == NODE_PIPE)	pipe_print(ast);
}

void	cmd_print(t_cmd *cmd)
{
	int	i = 0;

	if (!cmd->args.items)
		return ;

	printf("\nNODE_CMD:\n");
	if (cmd->redirs.items != NULL)
		redir_print(&cmd->redirs);
	while (cmd->args.items[i])
	{
		PERR("ARGS[%d]: %s\n", i, cmd->args.items[i]);
		i += 1;
	}
}

void	redir_print(t_redirs *p)
{
	size_t	i = 0;
	if (!p->items)
		return ;
	while (i < p->len)
	{
		PERR("FILES[%ld]: %s\n", i, p->items[i].path);
		PERR("TYPES[%ld]: %s\n", i, words[p->items[i].type]);
		i += 1;
	}
}
