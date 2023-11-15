/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/14 16:47:54 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>

# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>

# include "../libft/libft.h"
# include "./ms_mem.h"
# include "./ms_parser.h"
# include "./ms_exec.h"
# include "./ms_malloc.h"
# include "./ms_builtin.h"

#define SYTX_ERR "syntax error near unexpected token"

#define MS_STDERR 	2


t_array	ms_array_init();
void	ms_array_append(t_array *ptr, char *item);
void	ms_ast_print(t_ast *ast);
void	ms_table_add(struct s_fd_table *table, int fd);


void	cmd_print(t_cmd *cmq);
void	redir_print(struct s_redirs *p);
void	*ms_malloc(size_t size, char *file, int line);


void	rl_clear_history(void);
void	rl_replace_line (const char *text, int clear_undo);

char	**ms_envcpy(t_array *env);


void	ms_sig_handler(int sig);
int	    ms_catch_signal();

void	ms_expected_token(const t_token_type type);
int		ms_error(const char *fmt, ...);
void	ms_leaks(void);
void	ms_ast_destroy(t_ast *ast);
void	ms_close(struct s_fd_table *table);

int	    ms_cmd_path(char **cmd);
int	    ms_interactive_mode(void);


#endif //MINISHELL_H