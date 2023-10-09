/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:11:48 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: function allocates sufficient memory for a copy of the string s1, does the copy, and returns a pointer to it.
*/

char	*ft_strdup(const char *s1)
{
	char			*string;
	unsigned int	len;

	len = ft_strlen((char *)s1);
	//allocating memory for the pointer to s1, memory is allocated for the size of s1 + 1 being the null terminator.
	string = (malloc((len + 1) * sizeof(char)));
	if (!string)
		return (0);
	//copies the contents of s1 into string.
	ft_memcpy(string, s1, len * sizeof(char));
	string[len] = 0;
	return (string);
}
