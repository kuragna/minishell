/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utilts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:26:58 by aabourri          #+#    #+#             */
/*   Updated: 2024/01/08 17:20:18 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_array	ms_array_init(void)
{
	t_array	array;

	array.cap = 2;
	array.len = 0;
	array.items = malloc(sizeof(array.items) * array.cap);
	return (array);
}

void	ms_array_append(t_array *arr, char *item)
{
	const size_t	size = sizeof(arr->items);

	if (!arr->items)
		return ;
	if (arr->cap == arr->len)
	{
		arr->cap *= 2;
		arr->items = ft_realloc(arr->items, arr->len * size, arr->cap * size);
		if (!arr->items)
			return ;
	}
	arr->items[arr->len] = item;
	arr->len += 1;
}

struct s_string	ms_string_init(void)
{
	struct s_string	string;

	string.cap = 8;
	string.len = 0;
	string.data = malloc(sizeof(*string.data) * string.cap);
	return (string);
}

void	ms_char_append(struct s_string *str, const char c)
{
	const size_t	size = sizeof(*str->data);

	if (!str->data)
		return ;
	if (str->cap == str->len)
	{
		str->cap *= 2;
		str->data = ft_realloc(str->data, str->len * size, size * str->cap);
		if (!str->data)
			return ;
	}
	str->data[str->len] = c;
	str->len += 1;
}

void	ms_str_append(struct s_string *str, const char *s)
{
	while (s && *s)
	{
		ms_char_append(str, *s);
		s += 1;
	}
}
