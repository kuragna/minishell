/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:33:45 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description: Applies the function ’f’ to each character of the string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting from successive applications of ’f’.
The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
*/
#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str || !f)
	//the allocation would fail if the function f and string s were inexistent 
		return (NULL);
	i = 0;
	while (s[i])
	{
	//here we assign to each position of s the function f for each character in s
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
