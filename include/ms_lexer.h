#ifndef MS_LEXER_H
#define MS_LEXER_H

#include <stdlib.h>

typedef struct s_lexer t_lexer;


typedef enum e_token_type
{
	END, // end of input
	PIPE, // pipe
	LESS, // redirect input
	GREAT, // redirect output
	DOLLAR, 
	QUOTE,
	DQUOTE,
	DLESS, // redirect input with delimitar
	DGREAT, // redirect outut in append mode
	WORD, // command name and filename
} t_token_type;

typedef t_token_type (*t_fp)(t_lexer *);

typedef struct s_token
{
	t_token_type 	type;
	char			*lexeme;
	size_t			len;
} t_token;

struct s_lexer
{
	char *line;
	size_t len;
	size_t	pos;
	t_fp peek;
};


t_token			ms_token_next(t_lexer *l);
int				ms_is_token(int c);
int				ms_trim_left(t_lexer *l);

t_lexer 		ms_lexer_init(char *line);
int				ms_isquote(int c);

int				ms_consume(t_lexer *l, int (*f)(int));
t_token_type	ms_peek(t_lexer *l);

#endif //MS_LEXER_H
