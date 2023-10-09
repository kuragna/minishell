/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:05:05 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: converts the initial portion of the string pointed to by str to int representation
*/

int	ft_atoi(const char *str)
{
	int				i;
	int				signage;
	unsigned int	result;

	i = 0;
	result = 0;
	signage = 0;
	//incrementing index i every time it encounters isspace
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	//looking for plus or minus sign
	if (str[i] == 43 || str[i] == 45)
	{
	//incrementing signage while sign is a minus
		if (str[i++] == 45)
			signage++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	//adding digits to result
		result = ((str[i++] - '0') + (result * 10));
	if (result > 2147483647 && !signage)
	//because the INT MAX is 2147483647 anything above it cannot be returned as the int representation of a string
		return (-1);
	else if (result > 2147483648 && signage)
	//because the INT MIN is -2147483648 anything below it cannot be returned as the int representation of a string
		return (0);
	//if signage exists the result is negative
	else if (signage)
		return ((int)result * -1);
	//if result is positive and returned
	return ((int) result);
}
