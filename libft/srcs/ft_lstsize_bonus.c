/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:19:55 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: counts the number of nodes in a list.
*/

int	ft_lstsize(t_list *lst)
{
	int x;

	x = 0;
	if (!lst)
		return (0);
	//a non existant node in the list will have a null pointer.
	while (lst != NULL)
	{
	//moving through the list
		lst = lst -> next;
	//counting the number of nodes in the list
		x++;
	}
	//number of nodes in the list
	return(x);
}

















