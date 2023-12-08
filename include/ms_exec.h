/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:43:33 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/07 18:10:06 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

# include <errno.h>
# include <string.h>
# include "./ms_parser.h"
# include "./ms_lexer.h"

# define MS_STDIN	0
# define MS_STDOUT	1
# define MS_STDERR 	2
# define LEFT		0
# define RIGHT		1
# define MS_CNF		127
# define MS_PD		126
# define SYTX_ERR	"syntax error near unexpected token"

int		ms_io_handle(t_redirs *ptr, int *fd);
int		ms_cmd_path(char **cmd);

int		ms_error(const char *fmt, ...);
void	ms_error_exec(const char *cmd);

int		ms_exec_in(t_array args, int *fd);
int		ms_exec_pipe(t_ast *node, int *fd);
int		ms_exec_cmd(t_ast *node, int *fd);
int		ms_exec(t_ast *ast, int *fd);
int		ms_exec_in(t_array args, int *fd);


#endif //MS_EXEC_H
