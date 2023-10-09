/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:05:37 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: outputs the integer ’n’ to the given file descriptor.
*/

void ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
	//this number's length is to big to print in whole
		ft_putchar_fd('-', fd); 
		ft_putchar_fd('2', fd);
	//will recursively call ft_putnbr to call the rest of n
		ft_putnbr_fd(147483648, fd);
	}
	else if (n == 2147483647)
	{
	//this number's length is to big to print in whole
		ft_putchar_fd('2', fd);
	//will recursively call ft_putnbr to call the rest of n
		ft_putnbr_fd(147483647, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
	//will recursively call ft_putnbr to call the rest of n
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
	//enables us to go to previous digit
		ft_putnbr_fd(n / 10, fd);
	//prints digits
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}
