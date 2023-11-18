#include "../include/ms_lexer.h"
#include "../libft/libft.h" // For substr
#include <stdio.h>
#include "../include/minishell.h"

extern char	*words[];


t_lexer ms_lexer_init(char *line)
{
	t_lexer	lexer;

	lexer.pos = 0;
	lexer.start = 0;
	lexer.line = line;
	lexer.len = ft_strlen(line);
	return lexer;
}
t_token_type ms_peek(t_lexer *l)
{
	const char 		*tokens = "|<>";
	const size_t 	len = ft_strlen(tokens);
	size_t			i;

	i = 0;
	l->pos = ms_trim_left(l);
	if (l->pos >= l->len)
		return (NEWLINE);
	if (l->line[l->pos] == '<' && l->line[l->pos + 1] == '<')
		return (DLESS);
	if (l->line[l->pos] == '>' && l->line[l->pos + 1] == '>')
		return (DGREAT);
	if (l->line[l->pos] == '|' && l->line[l->pos + 1] == '|')
		return (OR);
	if (l->line[l->pos] == '&' && l->line[l->pos + 1] == '&')
		return (AND);
	while (i < len)
	{
		if (l->line[l->pos] == tokens[i])
		{
			return (i + PIPE);
		}
		i += 1;
	}
	return (WORD);
}


t_token	ms_token_next(t_lexer *l)
{
	t_token token;
	size_t	i;
	const char	*tokens = "|<>&";
	const size_t len = ft_strlen(tokens);

	i = 0;
	l->pos = ms_trim_left(l);
	ft_memset(&token, 0, sizeof(token));
	if (l->pos >= l->len) return token;
	if (ms_is_token(l->line[l->pos]))
	{
		while (i < len)
		{
			if (l->line[l->pos] == tokens[i])
			{
				i = 0;
				l->pos += 1;
			}
			else
				i += 1;
		}
		return token;
	}
	token.type = WORD;
	token.lexeme = ms_get_lexeme(l);
	return (token);
}

#if 0

int	main()
{
	while (1)
	{
		char	*line = readline("$> ");
		if (!line)
			break ;
		if (ms_check_quotes(line))
			continue;
		add_history(line);
		t_lexer lexer = ms_lexer_init(line);
		t_token_type type = ms_peek(&lexer);

		while (type != NEWLINE)
		{
			char	*lexeme = ms_token_next(&lexer).lexeme;
			printf("[TOKEN]: %s | [LEXEME]: %s\n", words[type], lexeme);
			type = ms_peek(&lexer);
		}
		printf("[LAST]: %s\n", words[ms_peek(&lexer)]);
	}
	return 0;
}

#endif
