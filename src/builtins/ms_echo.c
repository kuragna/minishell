/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:23:04 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/15 20:24:39 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '\"'

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

void	ms_echo_(char *text)
{
	// TODO: handle trim space
	// TODO: fix strign if has quotes function printing newline
	// TODO: with option -n
	// TODO: trim space from right
	// TODO: handle multiplle strings

	size_t	i = 0;
	size_t	j = 0;
	char *output;

	output = malloc(sizeof(char) * (ft_strlen(text) + 1));
	if (err_quotes_check(text) == 1)
	{
		ms_error("missing a quote\n");
		return ;
	}
	while (text && text[i])
	{
		//single quotes
		if (text[i] == SINGLE_QUOTE)
		{
			i++;
			while (text[i] && text[i] != SINGLE_QUOTE)
				output[j++] = text[i++];
			while (ft_isprint(text[++i]) == 1 && text[i] != SINGLE_QUOTE)
				output[j++] = text[i];
		}
		/*else if (text[i] == MS_SLASH)
			i += 1;
		else if (text[i] == DOUBLE_QUOTE)
		{
			i++;
			while (text[i] && text[i] != DOUBLE_QUOTE)
				output[j++] = text[i++];
			while (ft_isprint(text[++i]) == 1 && text[i] != DOUBLE_QUOTE)
				output[j++] = text[i];
		}
		printf("i = %zu | text[i] = %c | end loop\n", i, text[i]);*/
		i += 1;
	}
	output[j] = '\0';
	printf("%s\n", output);
	free(output);
}

void	ms_echo(char *text)
{
	(void) text;
	int	flag;
	size_t i = 0;

	flag = 1;
	if (ft_strncmp(text, "-n", 2) == 0 && (*(text + 2) == ' ' || *(text + 2) == '\0'))
	{
		flag = 0;
		i += 3;
	}
	while (text[i] != '\0')
	{
		if (text[i] == '\"')
			i += 1;
		if (ft_isspace(text[i]) && text[i] == '\\')
		{
			printf("here\n");
			i += 1;
		}
		ft_printf("%c", text[i]);
		i += 1;	
	}

	if (flag)
		printf("\n");
}
