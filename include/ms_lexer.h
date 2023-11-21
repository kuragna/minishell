/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:33:07 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/21 19:45:50 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include <stdlib.h>
# include "../include/ms_malloc.h"
# include "../libft/libft.h"

typedef struct s_lexer	t_lexer;
typedef struct s_token	t_token;
typedef enum e_token_type
{
	NEWLINE = 0,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	AND,
	OR,
	DOLLAR,
	WORD,
	COUNT,
}	t_token_type;

struct s_token
{
	t_token_type	type;
	char			*lexeme;
	size_t			len;
};

typedef struct s_array
{
	char	**items;
	size_t	cap;
	size_t	len;
}	t_array;

struct s_lexer
{
	char	*line;
	size_t	len;
	size_t	pos;
	t_array	*env;
};

t_lexer			ms_lexer_init(char *line);
t_token			ms_token_next(t_lexer *l);
t_token_type	ms_peek(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);
int				ms_error(const char *fmt, ...);
int				ms_check_quotes(const char *str);
void			*ms_malloc(size_t size, char *file, int line);
void			*ms_expected_token(const t_token_type type);
char			*ms_get_lexeme(t_lexer *l);
char			*ms_getenv(t_array *env, char *name);
int				ms_start(int c);

#endif //MS_LEXER_H
