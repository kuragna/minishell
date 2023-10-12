/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2023/10/12 23:33:03 by glacroix         ###   ########.fr       */
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

# include "../libft/libft.h"

#define MS_SLASH	'\\'
#define MS_S_QUOTE 	'\''
#define MS_D_QUOTE 	'\"'
#define MS_DOLLAR	'$'

#define MS_ERROR(...) ms_error(3, __VA_ARGS__)

#define MS_STDIN 	0
#define MS_STDOUT 	1
#define MS_STDERR 	2


/* ================= exit status ================= */
#define MS_CNF 127 // command to found
/* ================= exit status ================= */

/* ================= readline ================= */

// NOTE: see -> https://42born2code.slack.com/archives/CMX2R5JSW/p1624010153354900
void	rl_clear_history(void);
void	rl_replace_line (const char *text, int clear_undo);
/* ================= readline ================= */

/* ================= builtin ================= */

#include "../include/ms_builtin.h"

/* ================= builtin ================= */

/* ================= parsing ================= */

#include "../include/ms_lexer.h"

/* ================= parsing ================= */

/* ================= General ================= */

void	ms_error(const int size, ...); // exmple: minishell: djsk: command not found
void	ms_leaks(void);
void	ms_exec(char *cmd, char **args);

/* ================= General ================= */



#endif //MINISHELL_H
