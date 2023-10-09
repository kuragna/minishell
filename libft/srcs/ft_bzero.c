/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:47:30 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: writes n zeroed bytes to the string s. If n is zero, bzero() does nothing.
*/

void	ft_bzero(void *str, size_t n)
{
//memset functions replaces characters, with parameters 0 and n. It will replace in n characters in str with 0.
	ft_memset(str, 0, n);
}
