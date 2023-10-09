/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:57:35 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	j;
	size_t	y;

	y = ft_strlen((char *)src);
	x = 0;
	while (src[x] != 0)
		x++;
	if (dstsize != 0)
	{
		j = 0;
		while ((j + 1) < dstsize && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
	//null terminating the last position of dst
		dst[j] = 0;
	}
	return (y);
}
