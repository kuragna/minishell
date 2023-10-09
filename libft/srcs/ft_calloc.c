/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:05:47 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: allocate memory for count objects that are size of bytes of memory each and returns a pointer to the allocated memory. Memory is initialized with bytes of value zero.
*/

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;

	//memory is allocated to count objects of size of bytes of memory
	s = (unsigned char *)malloc(count * size);
	if (s == 0)
	//if the allocation fails, the pointer returns NULL.
		return (0);
	//else memory is allocated and the memory is initialized with bytes of value 0.
	ft_bzero(s, count * size);
	//after successful memory allocation, the pointer is returned.
	return (s);
}
