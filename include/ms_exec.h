/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:43:33 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 19:31:16 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

# include <errno.h>
# include <string.h>
# include "./ms_parser.h"
# include "./ms_lexer.h"

# define MS_STDIN		0
# define MS_STDOUT		1
# define MS_STDERR 		2
# define MS_LEFT		0
# define MS_RIGHT		1
# define MS_CNF			127
# define MS_PD			126
# define MS_SYTX_ERR	"syntax error near unexpected token"

int		ms_io_handle(t_redirs *ptr, t_data *data);
int		ms_cmd_path(t_array *env, char **cmd);

int		ms_error(const char *fmt, ...);
void	ms_error_exec(const char *cmd);

int		ms_exec_in(t_data *data);
int		ms_exec_pipe(t_ast *node, t_data *data);
int		ms_exec_cmd(t_ast *node, t_data *data);
int		ms_exec(t_ast *ast, t_data *data);

#endif //MS_EXEC_H
