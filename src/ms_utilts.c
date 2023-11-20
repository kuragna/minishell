/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utilts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:26:58 by aabourri          #+#    #+#             */
/*   Updated: 2023/11/18 20:03:54 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_interactive_mode(void)
{
	struct termios	attr;

	if (!isatty(MS_STDIN))
	{
		return (1);
	}
	if (tcgetattr(MS_STDIN, &attr) == -1)
	{
		return (1);
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(MS_STDIN, TCSANOW, &attr) == -1)
	{
		return (1);
	}
	return (0);
}

t_array	ms_array_init()
{
	t_array	array;

	array.cap = 2;
	array.len = 0;
	array.items = malloc(sizeof(array.items) * array.cap);
	return (array);
}

void	ms_array_append(t_array *arr, char *item)
{
	if (arr->cap == arr->len)
	{
		arr->cap *= 2;
		arr->items = ft_realloc(arr->items, sizeof(arr->items) * arr->cap);
	}
	arr->items[arr->len] = item;
	arr->len += 1;
}
