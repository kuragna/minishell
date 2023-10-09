/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:13:46 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: lexicographically compare up to n characters of the null-terminated strings s1 and s2. Characters after a '\0' are not compared.
*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = ((unsigned char *)s1);
	st2 = ((unsigned char *)s2);
	i = 0;
	while ((st1[i] != '\0' || st2[i] != '\0') && i < n)
	{
		if (st1[i] != st2[i])
	//if the strings are different
			return (st1[i] - st2[i]);
		i++;
	}
	//if the strings are identical then the function returns 0
	return (0);
}
