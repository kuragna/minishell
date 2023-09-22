/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2023/09/22 16:24:54 by aabourri         ###   ########.fr       */
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

# include <sys/stat.h>
# include <dirent.h>

# include <errno.h>

#include <fcntl.h>
#include <assert.h> // NOTE: need to remove it

/* NOTE: let's change it to third argument from main function instead global variable*/
extern char **environ; // NOTE: maybe we need to use third argument 

# include "../libft/libft.h"

#define MS_SLASH '\\'
#define MS_S_QUOTE '\''
#define MS_D_QUOTE '\"'
#define MS_ERR strerror(errno)

/* ================= readline ================= */

// NOTE: see -> https://42born2code.slack.com/archives/CMX2R5JSW/p1624010153354900
void	rl_clear_history(void);
void	rl_replace_line (const char *text, int clear_undo);
/* ================= readline ================= */

/* ================= builtin ================= */

#include "../include/ms_builtin.h"

/* ================= builtin ================= */

/* ================= General ================= */

char	*ms_trim_left(char *line);
void	ms_error(const char *res, const char *strerr); // exmple: minishell: djsk: command not found

/* ================= General ================= */



#endif //MINISHELL_H
