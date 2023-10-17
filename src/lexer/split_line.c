/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:29:19 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/17 20:36:32 by glacroix         ###   ########.fr       */
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


//need to free new_str in another function
char *remove_characters(char *text, char c)
{
	char *new_str;
	int i = 0;
	int j = 0;

	if (!text)
		return NULL;
	text = ft_strtrim(text, " ");
	new_str = malloc(sizeof(*new_str) * ft_strlen(text) + 1);
	if (!new_str)
		return NULL;
//	printf("[%s]\n", text);
	while (text[i])
	{
		if (text[i] && text[i] != c)
			new_str[j++] = text[i++];
		else
			i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

//INTERESTING = if you free string, you also free the nodes of the list
//TODO: add check for when SINGLE_QUOTE OR DOUBLE_QUOTE aren't closed
void single_quote_mode(t_token *token, char *line, size_t *start, size_t *end)
{
	char	*string;

	string = NULL;
	(*end)++;
	while (line[*end] && line[*end] != SINGLE_QUOTE)
		(*end)++;
	while (line[*end] && line[*end] != SPACE)
		(*end)++;
	string = ft_substr(line, *start, *end - *start);
	string = remove_characters(string, SINGLE_QUOTE);
	ft_lstadd_back(&token->list, ft_lstnew(string));
//	free(string);
	if (line[*end] != '\0')
		*start = *end + 1;
}

void double_quote_mode(t_token *token, char *line, size_t *start, size_t *end)
{
	char	*string;

	string = NULL;
	(*end)++;
	while (line[*end] && line[*end] != DOUBLE_QUOTE)
		(*end)++;
	while (line[*end] && line[*end] != SPACE)
		(*end)++;
	string = ft_substr(line, *start, *end - *start);
	string = remove_characters(string, DOUBLE_QUOTE); 
	ft_lstadd_back(&token->list, ft_lstnew(string));
	if (line[*end] != '\0')
		*start = *end + 1;
}

t_token *split_line(char *line)
{
	t_token	*token;
	size_t	start;
	size_t	end;
	size_t	len;
			

	token = NULL;
	start = 0;
	end = 0;
	token = malloc(sizeof(t_token));
	ft_memset(token, 0, sizeof(*token));
	len = ft_strlen(line);
	while (end < len)
	{
		while (ft_isspace(line[start]))
			start++;
		if (line[end] && line[end] == SINGLE_QUOTE)
			single_quote_mode(token, line, &start, &end);	
		else if (line[end] == DOUBLE_QUOTE)
			double_quote_mode(token, line, &start, &end);
		else if (line[end] == SPACE)
		{
			char *string = ft_substr(line, start, end - start);
			ft_lstadd_back(&token->list, ft_lstnew(string));
			if (line[end] != '\0')
				start = end + 1;
		}
		end++;
	}
	//char *string = ft_substr(line, start, end - start);
	//ft_lstadd_back(&token->list, ft_lstnew(string));
	return (token);
}

#if 1

int main()
{
	char *str = "ls -la | cat \"srcs -e\"";//readline("$> ");
	t_token *token = split_line(str);
	while (token->list != NULL)
	{
		printf("\ncontent = [%s]\n", token->list->content);
		token->list = token->list->next;
	}
	return (0);
}

#endif
