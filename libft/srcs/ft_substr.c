/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:47:48 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Allocates with malloc and returns a substring from the string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	length;

	if (s == NULL)
		return (NULL);
	//if the length of s is smaller than start, nothing can be copied
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(start + s);
	//if the length of s is smaller than len, then len takes the size of s
	if (length < len)
		len = length;
	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (NULL);
	//copies the string s to s1 from position s to len + 1
	ft_strlcpy(s1, (s + start), (len + 1));
	return (s1);
}
