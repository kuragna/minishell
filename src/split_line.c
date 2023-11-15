/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/11/15 18:26:34 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"
#include "../libft/libft.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'


/* #define malloc(size) ms_malloc(size, __FILE__, __LINE__)

void	*ms_malloc(size_t size, char *file, int line)
{
	void	*p = (malloc)(size);
	printf("%s:%d -> `%p`\n", file, line, p);
	return p;
} */

int check_quotes(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
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
char *ft_clean_string(char *string, size_t *pos)
{
	char 	quote;
	char	*new_content; 
	size_t	i;
	size_t	j;
	size_t	len_string;
	size_t	diff;


	i = 0;
	j = 0;
	len_string = ft_strlen(string);
	new_content = malloc(sizeof(char) * len_string + 1);
	if (!new_content)
		return NULL;
	while (i < len_string)
	{
		if (string[i] == SINGLE_QUOTE || string[i] == DOUBLE_QUOTE)
		{
			quote = string[i++];
			while (i < len_string && string[i] != quote)
				new_content[j++] = string[i++];
			i++;
		}
		else if (i < len_string && ms_is_token(string[i]))
		{
			diff = len_string - i;
			*pos -= diff;
			new_content[j] = '\0';
			return (new_content);
		}
		else
			new_content[j++] = string[i++];
	}
	new_content[j] = '\0';
	return (new_content);
}

char	*quote(t_lexer *lex, char quote)
{
	char	*str;
	char	*str_f;
	size_t 	quote_pos;
	
	quote_pos = lex->pos;
	lex->pos++;
	while (lex->pos < lex->len && lex->line[lex->pos] != quote)
		lex->pos++;
	while (lex->pos < lex->len && !ft_isspace(lex->line[lex->pos]))
		lex->pos++;
	str = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	str_f = ft_clean_string(str, &lex->pos);
	free(str);
	if (lex->line[lex->pos] != '\0')
		lex->start = lex->pos + 1;
	return (str_f);
}

#if 0

int main()
{
	//atexit(ft_leaks);
// 	t_lexer	lex;
// 	t_token *token;

	struct s_lex lex;


	while (1)
	{
		ft_memset(&lex, 0, sizeof(lex));
		lex.line = readline("$> ");
		if (!lex.line)
			break ;
		lex.len = ft_strlen(lex.line);
		char	*str = dquote(&lex);
		printf("pos -> [%s] | pos = %ld\n", &lex.line[lex.pos], lex.pos);
		printf("[RE]: %s\n", str);

		free(str);


		add_history(lex.line);
		free(lex.line);
	}
	return (0);
}

#endif

