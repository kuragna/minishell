/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:20:00 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: compares two strings up to n bytes and returns 0 if they are identical.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			p;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = ((unsigned char *)s1);
	st2 = ((unsigned char *)s2);
	p = 0;
	while (p < n)
	{
	//if there is a difference between both strings, the difference is returned
		if (st1[p] != st2[p])
			return (st1[p] - st2[p]);
		p++;
	}
	//if those are identical, 0 is returned
	return (0);
}
