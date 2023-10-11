/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:23:04 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/11 20:36:39 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int count_single_quotes(char *text)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (text[++i])
	{
		if (text[i] == SINGLE_QUOTE)
			count++;
	}
	return (count);
}

static int count_double_quotes(char *text)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (text[++i])
	{
		if (text[i] == DOUBLE_QUOTE)
			count++;
	}
	return (count);
}

static int	err_quotes_check(char *text)
{
	int n_single_quotes = count_single_quotes(text);
	int n_double_quotes = count_double_quotes(text);

	if (n_single_quotes % 2 != 0 || n_double_quotes % 2 != 0)
		return (1);
	return (0);
}

void	ms_echo(char *text)
{
	// TODO: handle trim space
	// TODO: fix string if has quotes function printing newline
	// TODO: with option -n
	// TODO: trim space from right
	// TODO: handle multiplle strings

	//TODO: change char *text to char **input
	//TODO: input received for ms_echo is already cleaned by parsing
	size_t	i = 0;
	size_t	j = 0;
	char *output;

	if (text && *text == MS_DOLLAR)
		text = getenv(text + 1);
	if (err_quotes_check(text) == 1)
	{
		MS_ERROR("missing a quote\n");
		return;
	}
	output = malloc(sizeof(char) * (ft_strlen(text) + 1));
	while (text && text[i])
	{
		
		//single quotes
		if (text[i] == SINGLE_QUOTE)
		{
			i++;
			if (text[i] == DOUBLE_QUOTE)
			{
				i++;
				while (text[i] && text[i] != DOUBLE_QUOTE)
					output[j++] = text[i++];
				i++;
			}
			while (text[i] && text[i] != SINGLE_QUOTE && text[i] != DOUBLE_QUOTE)
				output[j++] = text[i++];
		}
		else if (text[i] == DOUBLE_QUOTE)
		{
			i++;
			while (text[i] && text[i] != DOUBLE_QUOTE && text[i] != SINGLE_QUOTa)
				output[j++] = text[i++];
	//		while (ft_isprint(text[++i]) == 1 && text[i] != DOUBLE_QUOTE)
	//			output[j++] = text[i];
		}
		/*else if (text[i] == MS_SLASH)
			i++;
		else
			output[j++] = text[i++];*/
	}
	output[j] = '\0';
	printf("%s\n", output);
	free(output);
}
