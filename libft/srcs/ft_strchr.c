/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:16:10 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: function locates the first occurrence of c (converted to a char) in the string pointed to by s.  The terminating null character is considered to be part of the string.
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (const char)c)
		//returns the first occurence of c in the string s starting from the position in s which is equal to char c
			return ((char *)s);
		s++;
	}
	if (*s == (const char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}
