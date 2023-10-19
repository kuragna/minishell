/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:36:26 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/19 17:27:44 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *split_line_op_quotes(char *line)
{
	//if the string doesn't have any space
	//everytime a double quote is encountered and its neighbor is the next one we skip it
	//we join the letters, nums, and anything not being a quote
	//we give back the string cleaned
	char	*result = malloc(1000);
	size_t		i = 0;
	size_t		j = 0;

	size_t len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] && (line[i] != SINGLE_QUOTE && line[i] != DOUBLE_QUOTE))
		{
			result[j] = line[i];
			j++;
		}
		else if (line[i] && line[i] == SINGLE_QUOTE && line[i+1] == SINGLE_QUOTE)
			i += 2;
		else if (line[i] && line[i] == DOUBLE_QUOTE && line[i+1] == DOUBLE_QUOTE)
			i += 2;
		//result[j] = 0;
		//printf("line: %s\n", &line[i]);
		//printf("re: %s\n", &result[j]);
		i++;
	}
	printf("i = %ld | len = %ld\n", i, len);
	//if (line[i] == '\0') result[j++] = line[len - 1];
	result[j] = '\0';
	return (result);
}

int main()
{
	char	*str = "p""''''w''''''""""""''''''''''''''''''''''''''''''''d";
	char	*str1 = """""""1234''''''5678''''''91";
	char *result = split_line_op_quotes(str);
	char *result1 = split_line_op_quotes(str1);
	printf("result = %s | result1 =  %s\n", result, result1);
	return (0);
}
