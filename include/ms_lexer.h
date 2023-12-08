/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:33:07 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/07 18:08:15 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include <stdlib.h>
# include "../include/ms_malloc.h"
# include "../libft/libft.h"

extern struct s_context	g_ctx;

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

typedef struct s_lexer
{
	char	*line;
	size_t	len;
	size_t	pos;
}	t_lexer;

struct s_fd_table
{
	int		fds[1024];
	size_t	len;
};

struct s_context
{
	struct s_fd_table	table;
	t_array				*env;
	char				**items;
	int					exit_status;
	int					flag;
	// TODO: save child pid to kill it
};

t_token_type	ms_peek(t_lexer *l);
t_lexer			ms_lexer_init(char *line);
char			*ms_token_next(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);
int				ms_error(const char *fmt, ...);
int				ms_check_quotes(const char *str);
void			*ms_malloc(size_t size, char *file, int line);
void			*ms_error_token(const t_token_type type, void *ptr);
char			*ms_getenv(const char *name);
int				ms_start(int c);

struct s_string	ms_string_init(void);
void			ms_char_append(struct s_string *str, const char c);
void			ms_str_append(struct s_string *str, const char *s);

int				ms_is_usalnum(int c);
int				ms_is_quote(int c);
int				ms_isspecial(int c);
char			*ms_get_lexeme(t_lexer *l);
void			ms_expand_exit_status(t_lexer *l, struct s_string *word);
void			ms_lexeme_(t_lexer *l, struct s_string *word);
void			ms_quote_consume(t_lexer *l, struct s_string *word, char c);

#endif //MS_LEXER_H
