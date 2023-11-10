#ifndef MS_LEXER_H
#define MS_LEXER_H

#include <stdlib.h>
#include "../include/ms_malloc.h"

typedef struct s_lexer t_lexer;
typedef struct s_token t_token;


typedef enum e_token_type
{
	NEWLINE,	/* end of input */
	PIPE,		/* Pipe input/output between process */
	LESS,		/* Redirect input */
	GREAT,		/* Redirect output */
	DLESS, 		/* Redirect input with delimitar */
	DGREAT,		/* Redirect outut in append mode */
	DOLLAR,		/* Expand value from $VAR */
	QUOTE,		/* Expand value from 'single quote' */
	DQUOTE,		/* Expand value from 'dounle quote' */
	WORD,		/* Commands, Args and File names */
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
	size_t	pos;
};


t_lexer 		ms_lexer_init(char *line);
t_token			ms_token_next(t_lexer *l);
t_token_type	ms_peek(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);
int				ms_is_quote(int c);
int				ms_consume(t_lexer *l, int (*f)(int));
void			ms_expected_token(const t_token_type type);
void			*ms_malloc(size_t size, char *file, int line);



#endif //MS_LEXER_H
