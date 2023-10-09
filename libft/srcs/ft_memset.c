/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:22:49 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: write n bytes of value c to the string str.
*/

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned long	x;

	x = 0;
	while (x < n)
	{
		//starting from str[x] position are converted to c.
		((unsigned char *)str)[x] = c;
		x++;
	}	
	return (str);
}
