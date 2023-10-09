/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:47:24 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Allocates with malloc and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.
*/

char	*ft_strtrim(char const *_s, char const *cut)
{
	char	*s;
	size_t	size;

	s = ((char *)_s);
	if (!_s || !cut)
		return (NULL);
	//find the first occurence of cut in string s and takes it out
	while (*s && ft_strchr(cut, *s))
		s++;
	size = ft_strlen(s);
	//find the last occurence of cut in string s and takes it out
	while (size && ft_strrchr(cut, s[size]))
		size--;
	//returning the remaining characters from s
	return (ft_substr(s, 0, size + 1));
}
