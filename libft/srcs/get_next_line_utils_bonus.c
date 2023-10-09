/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:55:53 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * Ft_strjoin() takes two strings and returns a new string that is the
 * concatenation of the two strings
 * 
 * @param s1 the first string to be joined
 * @param s2 "Hello"
 * 
 * @return A pointer to the new string.
 */
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	s3 = malloc(sizeof(char) * ((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1)));
	if (!s3)
	{
		free(s3);
		return (NULL);
	}
	i = -1;
	while (s1[++i] != 0)
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free (s1);
	return (s3);
}

/**
 * The function ft_strlen() takes a string as an argument and returns the length
 * of the string
 * 
 * @param str This is the string that we are going to be finding the length of.
 * 
 * @return The length of the string.
 */
size_t	ft_strlen_gnl(char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}	
	return (x);
}
