/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utilts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:35:46 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 19:44:50 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_parser.h"

t_ast	*ms_and_or_node(t_ast_node node_type, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->type = node_type;
	ast->and_or.left = left;
	ast->and_or.right = right;
	return (ast);
}

t_ast	*ms_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->pipe.left = left;
	node->pipe.right = right;
	return (node);
}

t_redir	*ms_redir_node(char *path, t_token_type type)
{
	t_redir	*node;

	node = malloc(sizeof(*node));
	if (node)
	{
		node->path = path;
		node->type = type;
	}
	return (node);
}

t_ast	*ms_cmd_node(void)
{
	t_ast	*node;
	t_cmd	cmd;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	cmd.args = ms_array_init();
	ft_memset(&cmd.redirs, 0, sizeof(cmd.redirs));
	node->type = NODE_CMD;
	node->cmd = cmd;
	return (node);
}

t_redirs	ms_redirs_init(void)
{
	t_redirs	items;

	items.cap = 2;
	items.len = 0;
	items.items = malloc(sizeof(*items.items) * items.cap);
	return (items);
}