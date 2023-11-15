#ifndef MS_LEXER_H
#define MS_LEXER_H

#include <stdlib.h>
#include "../include/ms_malloc.h"
#include "../libft/libft.h"

typedef struct s_lexer t_lexer;
typedef struct s_token t_token;


typedef enum e_token_type
{
	NEWLINE,	// 0 /* end of input */
	PIPE,		// 1 /* Pipe input/output between process */
	LESS,		// 2 /* Redirect input */
	GREAT,		// 3 /* Redirect output */
	DLESS, 		// 4 /* Redirect input with delimitar */
	DGREAT,		// 5 /* Redirect outut in append mode */
	AND,		// 6
	OR,			// 7
	DOLLAR,		// 8 /* Expand value from $VAR */
	QUOTE,		// 9 /* Expand value from 'single quote' */
	DQUOTE,		// 10 /* Expand value from 'dounle quote' */
	WORD,		// 11 /* Commands, Args and File names */
} t_token_type;

struct s_token
{
	t_token_type 	type;
	char			*lexeme;
	size_t			len;
	// TODO: add more things to get quotes and dollar sign
};

struct s_lexer
{
	char *line;
	size_t len;
	size_t	start;
	size_t	pos;
};


t_lexer 		ms_lexer_init(char *line);
t_token			ms_token_next(t_lexer *l);
t_token_type	ms_peek(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);
int				ms_is_quote(int c);
int				ms_consume(t_lexer *l, int (*f)(int));
char			*quote(t_lexer *lex, char quote);

void			ms_expected_token(const t_token_type type);
void			*ms_malloc(size_t size, char *file, int line);
int				ms_error(const char *fmt, ...);
int check_quotes(char *str);



#endif //MS_LEXER_H
