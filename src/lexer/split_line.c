/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/12 23:45:28 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Delimiters are | >> > < " '
 * first split with delimiters
 * then single quotes and double quotes
 * then spaces
 */

/**creating a modified split to split a line by all delimiters
 * 1) we move along the line looking for spaces once we encounter a space we take the starting position and the i - 1 pos and create a substring and then listaddback
 * 2) if we encounter a quote (be it a single or double quote) we enter in quote mode:
 * 			we are looking for the next identical quote to create our token however once we encounter it, we do not close the word until we encounter a space
 * 			then same thing => substring => listaddback
 * 3) at the end we will have a list of tokens, some will be words, some will be delimiters but we don't know this yet
 * 4) here we will go through our list of tokens and mark the tokens that are delimiters as delim_tokens
 * 5) we will look at the list and now determine what are the word types: cmd, args or file
 * 6) I think that's it :)
 * */

// this was a test but it's the wrong approach, it is not optimal to count words when we don't know how long our line will; hence the option of using lists.

/*
static int	word_count(char const *str, char *delimiters)
{
	int word_count, i, j;
	char const *temp;
	
	i=0;
	while (delimiters && delimiters[i])
		printf("delimiters[i] = %c\n", delimiters[i++]);
	word_count = 0;
	i = 0;
	j = 0;
	while (delimiters[i])
	{
		temp = str;
		while (*temp)
		{
			while (*temp && *temp == delimiters[i])
				temp++;
			if (*temp)
				word_count++;
			while (*temp && *temp != delimiters[i])
				temp++;
		}
		i++;
	}
	return (word_count);
}

int main()
{
	char const *str = "ls -la";
	char delimiters[4] = {'|', '>', '<', 0};
	printf("str [ %s ]\n", str);
	printf("word count = %d\n", word_count(str, delimiters));
	return (0);
}

char **ft_split_multiple_c(char const *str, char *str)
{
	char	**tokens;
	char	**delimiters;
	int		nb_words;
	int		j = 0;

	if (!str)
		return (NULL);
	delimiters = ft_split(str, 32);
	nb_words = word_count(s, delimiters);
	
}

char **split_line(char *line)
{
	char **args	= ft_split(line, '|');

	return args;
}*/
