#include "../include/ms_lexer.h"
#include <stdio.h>

struct s_string
{
	char	*data;
	size_t	cap;
	size_t	len;
};

static int	ms_is_quote(int q)
{
	return (q == '\"' || q == '\'');
}

static int	ms_str_append(struct s_string *str, char c)
{
	if (str->cap == str->len)
	{
		str->cap *= 2;
		str->data = ft_realloc(str->data, sizeof(*str->data) * str->cap);
		if (!str->data)
			return (1);
	}
	str->data[str->len] = c;
	str->len += 1;
	return (0);
}

static void	ms_quote_consume(t_lexer *l, struct s_string *str, char c)
{
	//printf("must be quote: `%c`\n", c);
	while (l->pos < l->len && l->line[l->pos] != c)
	{
		//printf("append: [%c]\n", l->line[l->pos]);
		ms_str_append(str, l->line[l->pos]);
		l->pos += 1;
	}
	l->pos += 1;
}


char	*ms_get_lexeme(t_lexer *l)
{
	struct s_string	string;
	char			quote;

	string.cap = 8;
	string.len = 0;
	string.data = malloc(sizeof(*string.data) * string.cap);
	if (!string.data)
		return (NULL);
	while (l->pos < l->len && !ms_is_token(l->line[l->pos]))
	{
		if (!ms_is_quote(l->line[l->pos]))
		{
			ms_str_append(&string, l->line[l->pos]);
			l->pos += 1;
		}
		else
		{
			quote = l->line[l->pos];
			l->pos += 1;
			ms_quote_consume(l, &string, quote);
		}
	}
	ms_str_append(&string, '\0');
	return string.data;
}

int ms_check_quotes(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (ms_is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
				return (ms_error("minishell: unclosed quote: %s\n", &quote));
		}
		i++;
	}
	return (0);
}
