/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:12:49 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Iterates the list ’lst’ and applies the function ’f’ on the content of each node.
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
*/

void ft_lstiter(t_list *lst, void (*f)(void *))
{
//if the list doesn't exists, the function does nothing
	if (!lst)
		return ;
	while (lst)
	{
	//function f is applied to a node of the list
		(*f)(lst->content);
	//moving to the next node
		lst = lst->next;
	}
}
