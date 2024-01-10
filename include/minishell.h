/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/10 13:13:28 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "./ms_parser.h"
# include "./ms_exec.h"
# include "./ms_builtin.h"

extern int	g_status;

t_array	ms_array_init(void);
void	ms_array_append(t_array *ptr, char *item);

void	ms_table_add(struct s_fd_table *table, int fd);

void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);

void	ms_leaks(void);
void	ms_ast_destroy(t_ast *ast);
void	ms_close(struct s_fd_table *table);
int		ms_signal(void);
int		ms_error(const char *fmt, ...);
int		ms_cmd_path(t_array *env, char **cmd);
int		ms_interactive_mode(void);
void	*ms_error_token(const t_token_type type, void *ptr);
char	**ms_envcpy(t_array *env);

#endif //MINISHELL_H