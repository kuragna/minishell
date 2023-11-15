//#include "../include/minishell.h"

#include "../include/ms_parser.h"

static void	ms_pipe_destroy(t_ast *ast)
{
	t_ast *l = ast->pipe.left;
	t_ast *r = ast->pipe.right;

	ms_ast_destroy(l);
	ms_ast_destroy(r);
}

static void	ms_redirs_destroy(t_redir *items, size_t size)
{
	size_t	i;

	i = 0;
	if (!items)
		return ;
	while (i < size)
	{
		free(items[i].path);
		items[i].path = NULL;
		i += 1;
	}
	free(items);
	items = NULL;
}

static void	ms_cmd_destroy(t_cmd *cmd)
{
	size_t i;

	i = 0;
	ms_redirs_destroy(cmd->redirs.items, cmd->redirs.len);
	ft_free(cmd->args.items);
}


void	ms_ast_destroy(t_ast *ast)
{
	if (!ast)
		return ;
	// add 'AND' and 'OR' tokens
	if (ast->type == NODE_PIPE)
		ms_pipe_destroy(ast);
	if (ast->type == NODE_CMD)
		ms_cmd_destroy(&ast->cmd);
	free(ast);
	ast = NULL;
}