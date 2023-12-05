/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:51 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/05 15:55:57 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_envcpy(t_array *env)
{
	size_t	i;
	t_array	e;

	i = 0;
	e = ms_array_init();
	if (!e.items)
		return (NULL);
	while (i < env->len)
	{
		if (ft_strchr(env->items[i], '='))
			ms_array_append(&e, env->items[i]);
		i += 1;
	}
	ms_array_append(&e, NULL);
	return (e.items);
}

// TODO: change the name
void	ms_lexeme_(t_lexer *l, struct s_string *word)
{
	char	quote;

	if (ms_is_quote(l->line[l->pos]))
	{
		quote = l->line[l->pos];
		l->pos += 1;
		ms_quote_consume(l, word, quote);
	}
	while (l->pos < l->len)
	{
		if (ms_is_quote(l->line[l->pos]) || ms_is_token(l->line[l->pos]))
			break ;
		ms_char_append(word, l->line[l->pos]);
		l->pos += 1;
		if (l->line[l->pos] == '$')
			break ;
	}
}
