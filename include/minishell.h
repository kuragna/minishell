/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2023/10/16 18:54:50 by aabourri         ###   ########.fr       */
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
# include <dirent.h>
# include <termios.h>

# include "./ms_mem.h"
# include "../libft/libft.h"
# include "../include/ms_builtin.h"


#define MS_STDIN 	0
#define MS_STDOUT 	1
#define MS_STDERR 	2


void	rl_clear_history(void);
void	rl_replace_line (const char *text, int clear_undo);


void	ms_sig_handler(int sig);
int	    ms_catch_signal();


int		ms_error(const char *fmt, ...);
void	ms_leaks(void);


int	    ms_cmd_path(char **cmd);
int	    ms_interactive_mode(void);




#endif //MINISHELL_H