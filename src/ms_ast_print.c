#include "../include/minishell.h"

//#include "main.c"

extern char *words[];

void	pipe_print(t_ast *ast)
{
	ms_ast_print(ast->pipe.left);
	ms_ast_print(ast->pipe.right);
}

void	ms_ast_print(t_ast *ast)
{
	if (ast->type == NODE_CMD)
		cmd_print(&ast->cmd);
	if (ast->type == NODE_PIPE)
	{
		pipe_print(ast);
	}
}

void	cmd_print(t_cmd *cmd)
{
	size_t i = 0;

	if (cmd->redirs.items != NULL)
		redir_print(&cmd->redirs);
	PERR("\n ARGS:\n");
	while (cmd->args.argv[i])
	{
		PERR("	%s\n", cmd->args.argv[i]);
		i += 1;
	}
}

void	redir_print(struct s_redirs *p)
{
	size_t i = 0;

	PERR("FILES:\n");

	if (!p->items)
		return ;
	while (i < p->len)
	{
		PERR("    %s\n", p->items[i].path);
		PERR("    %s\n", words[p->items[i].type]);
		i += 1;
	}
}
