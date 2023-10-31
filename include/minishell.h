/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:04:35 by aabourri          #+#    #+#             */
/*   Updated: 2023/10/31 16:00:09 by aabourri         ###   ########.fr       */
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

enum e_type
{
	END, // end of input
	PIPE, // pipe
	LESS, // redirect input
	GREAT, // redirect output
	DLESS, // redirect input with delimitar
	DGREAT, // redirect outut in append mode
	WORD, // command name and filename
};

typedef struct
{
	char *line;
	size_t len;
	size_t	pos;
} t_lexer;


void	rl_clear_history(void);
void	rl_replace_line (const char *text, int clear_undo);


void	ms_sig_handler(int sig);
int	    ms_catch_signal();


int		ms_error(const char *fmt, ...);
void	ms_leaks(void);


int	    ms_cmd_path(char **cmd);
int	    ms_interactive_mode(void);

int		ms_ismetachar(int c);
int		ms_trim_left(t_lexer *l);
t_lexer ms_lexer_init(char *line);
int		ms_isquote(int c);
int		ms_consume(t_lexer *l, int (*f)(int));
enum e_type ms_peek(t_lexer *l);




#endif //MINISHELL_H