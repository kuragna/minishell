/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:37:42 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/04 13:52:11 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_parser.h"
#include "../include/ms_builtin.h"

//extern char		*words[]; // delete it later

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

static int	ms_parse_files(struct s_redirs *ptr, t_lexer *lexer)
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
			ms_expected_token(ms_peek(lexer));
			return (1);
		}
		ms_redir_add(ptr, ms_token_next(lexer), type);
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
		if (ms_parse_files(&node->cmd.redirs, lexer))
			return (NULL);
		if (ms_parse_args(&node->cmd, lexer))
			return (NULL);
		ms_parse_args(&node->cmd, lexer);
	}
	ms_array_append(&node->cmd.args, NULL);
	return (node);
}

// t_ast	*ms_parse_and_or(t_lexer *lexer)
// {
// 	t_ast			*left;
// 	t_ast			*right;
// 	t_token_type	type;
// 	t_ast_node		ast_node;

// 	type = ms_peek(lexer);
// 	if (type == AND || type == OR)
// 		return (ms_expected_token(type));
// 	left = ms_parse_pipe(lexer);
// 	if (!left)
// 		return (NULL);
// 	type = ms_peek(lexer);
// 	if (type == AND || type == OR)
// 	{
// 		ast_node = NODE_AND;
// 		if (type != AND)
// 			ast_node = NODE_OR;
// 		ms_token_next(lexer);
// 		if (ms_peek(lexer) != WORD)
// 			return (ms_expected_token(ms_peek(lexer)));
// 		right = ms_and_or_node(ast_node, left, ms_parse_and_or(lexer));
// 		return (right);
// 	}
// 	return (left);
// }

// TODO: fix double free in error case

t_ast	*ms_parse_pipe(t_lexer *lexer)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;

	type = ms_peek(lexer);
	if (type == PIPE)
		return (ms_expected_token(type));
	left = ms_parse_redir(lexer);
	if (!left)
		return (NULL);
	if (ms_peek(lexer) == PIPE)
	{
		ms_token_next(lexer);
		type = ms_peek(lexer);
		if (type == NEWLINE)
			return (ms_expected_token(type));
		right = ms_pipe_node(left, ms_parse_pipe(lexer));
		if (!right)
			return (NULL);
		return (right);
	}
	return (left);
}
