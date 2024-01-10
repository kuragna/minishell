/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexeme_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:32:50 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/10 13:27:09 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_lexer.h"

extern int	g_status;

int	ms_is_usalnum(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ms_is_quote(int c)
{
	return (c == '\"' || c == '\'');
}

int	ms_is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == '~' || ms_is_quote(c));
}

void	ms_expand_exit_status(t_lexer *l, struct s_string *word)
{
	char	*str;

	if (l->line[l->pos] != '?')
		return ;
	str = ft_itoa(g_status);
	if (!str)
		return ;
	ms_str_append(word, str);
	free(str);
	l->pos += 1;
}

int	ms_check_quotes(const char *str)
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
			if (!str[i] || str[i] != quote)
			{
				ms_error("minishell: unclosed quote: %c\n", quote);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
