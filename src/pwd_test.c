/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:36:26 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/20 15:40:13 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *split_line_op_quotes(char *line)
{
	//if the string doesn't have any space
	//everytime a double quote is encountered and its neighbor is the next one we skip it
	//we join the letters, nums, and anything not being a quote
	//we give back the string cleaned
	char		*result = malloc(1000);
	size_t		i = 0;
	size_t		j = 0;

	size_t len = ft_strlen(line);
	printf("len = %ld\n", len);
	while (i < len)
	{
		if (line[i] && line[i] == SINGLE_QUOTE && line[i+1] == SINGLE_QUOTE)
			i += 2;
		else if (line[i] && line[i] == DOUBLE_QUOTE && line[i+1] == DOUBLE_QUOTE)
			i += 2;
		else 		
		{
			result[j] = line[i++];
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}

#if 0

int main()
{
	while (1)
	{
		char *str = readline("$> ");
		ms_exit(str);
		add_history(str);
		char *result = split_line_op_quotes(str);
		printf("result = [%s]\n", result);
	}
	return (0);
}

#endif
