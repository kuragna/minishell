/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:52:50 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/04 13:54:11 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"

#include "../include/ms_parser.h"

static void	ms_pipe_destroy(t_ast *ast)
{
	ms_ast_destroy(ast->pipe.left);
	ms_ast_destroy(ast->pipe.right);
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
	size_t	i;

	i = 0;
	ms_redirs_destroy(cmd->redirs.items, cmd->redirs.len);
	ft_free(cmd->args.items);
}

void	ms_ast_destroy(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
		ms_pipe_destroy(ast);
	if (ast->type == NODE_CMD)
		ms_cmd_destroy(&ast->cmd);
	free(ast);
	ast = NULL;
}
