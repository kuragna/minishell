/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:37:42 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/11 15:53:19 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_parser.h"
#include "../include/ms_builtin.h"

extern int	g_status;

static int	ms_parse_args(t_cmd *cmd, t_lexer *lexer)
{
	char	*arg;

	if (cmd->args.items == NULL)
		return (1);
	while (ms_peek(lexer) == WORD)
	{
		arg = ms_token_next(lexer);
		ms_array_append(&cmd->args, arg);
	}
	return (0);
}

static int	ms_parse_files(t_ast *ast, t_lexer *lexer)
{
	char			*str;
	t_token_type	type;

	if (ast->cmd.redirs.items == NULL)
		return (1);
	while (1)
	{
		type = ms_peek(lexer);
		if (!(type >= LESS && type <= DGREAT))
			break ;
		lexer->prev = type;
		ms_token_next(lexer);
		if (ms_peek(lexer) != WORD)
			return (ms_error_token(ms_peek(lexer), NULL), 1);
		str = ms_token_next(lexer);
		if (!str)
		{
			ast->cmd.redirs.len = 0;
			g_status = 1;
			break ;
		}
		ms_redir_add(&ast->cmd.redirs, str, type);
	}
	return (0);
}

static t_ast	*ms_parse_cmd(t_lexer *lexer)
{
	t_ast	*node;

	node = ms_cmd_node();
	if (node)
		ms_parse_args(&node->cmd, lexer);
	return (node);
}

static t_ast	*ms_parse_redir(t_lexer *lexer)
{
	t_ast			*node;
	t_token_type	type;

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
		if (!(ms_peek(lexer) >= LESS && ms_peek(lexer) <= DGREAT))
			break ;
		if (ms_parse_files(node, lexer))
			return (NULL);
		if (ms_parse_args(&node->cmd, lexer))
			return (NULL);
		ms_parse_args(&node->cmd, lexer);
	}
	ms_array_append(&node->cmd.args, NULL);
	return (node);
}

t_ast	*ms_parse_pipe(t_lexer *lexer)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;

	type = ms_peek(lexer);
	if (type == PIPE)
		return (ms_error_token(type, NULL));
	left = ms_parse_redir(lexer);
	if (!left)
		return (NULL);
	if (ms_peek(lexer) == PIPE)
	{
		ms_token_next(lexer);
		type = ms_peek(lexer);
		if (type == NEWLINE)
			return (ms_error_token(type, NULL));
		right = ms_pipe_node(left, ms_parse_pipe(lexer));
		if (!right)
			return (NULL);
		return (right);
	}
	return (left);
}
