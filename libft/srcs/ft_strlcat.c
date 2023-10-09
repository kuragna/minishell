/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:12 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description:  appends string src to the end of dst.  It will append at most dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless dstsize is 0 or the original dst string was longer than dstsize
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	x;

	x = ft_strlen((char *)src);
	j = 0;
	while (dst[j] && j < dstsize)
		j++;
	i = 0;
//the return value cannot be above dstsize
	while (src[i] && i + j + 1 < dstsize)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (i != 0)
		dst[i + j] = 0;
//returns initial length of dst plus length of src
	return (x + j);
}
