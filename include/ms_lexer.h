/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:33:07 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/10 13:13:16 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef enum e_token_type
{
	NEWLINE = 0,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	WORD,
}	t_token_type;

typedef struct s_array
{
	char	**items;
	size_t	cap;
	size_t	len;
}	t_array;

struct s_string
{
	char	*data;
	size_t	cap;
	size_t	len;
};

struct s_fd_table
{
	int		fds[9000];
	size_t	len;
};

typedef struct s_data
{
	t_array				*env;
	char				**argv;
	int					fd[2];
	int					pipe_flag;
	int					heredoc_flag;
	int					quotes_flag;
	struct s_fd_table	table;
}	t_data;

typedef struct s_lexer
{
	char			*line;
	size_t			len;
	size_t			pos;
	t_data			data;
	t_token_type	prev;
}	t_lexer;

t_token_type	ms_peek(t_lexer *l);
void			ms_lexer_init(t_lexer *l, const char *line);
char			*ms_token_next(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);
int				ms_error(const char *fmt, ...);
int				ms_check_quotes(const char *str);
char			*ms_getenv(t_array *env, const char *name);

struct s_string	ms_string_init(void);
void			ms_char_append(struct s_string *str, const char c);
void			ms_str_append(struct s_string *str, const char *s);

int				ms_is_start(int c);
int				ms_is_usalnum(int c);
int				ms_is_quote(int c);
int				ms_is_special(int c);

int				ms_open(const char *path, int oflag, int mode);

char			*ms_lexeme_value(int flag, struct s_string *word, t_lexer *l);
char			*ms_get_lexeme(t_lexer *l);
void			ms_expand_exit_status(t_lexer *l, struct s_string *word);
void			ms_lexeme_(t_lexer *l, struct s_string *word);
void			ms_quote_consume(t_lexer *l, struct s_string *word, char c);
int				ms_expansion(t_lexer *l, struct s_string *word);

char			*ms_heredoc_dlmtr(t_lexer *l, struct s_string *word);
char			*ms_heredoc_expansion(char *name, t_data *data);
void			ms_heredoc_sig_handler(int sig);
void			ms_heredoc(const int fd, const char *dlmtr, t_data *data);
int				ms_heredoc_child(char *file_path, char *dlmtr, t_data *data);

#endif //MS_LEXER_H
