/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:24:54 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Iterates the list ’lst’ and applies the function ’f’ on the content of each node. 
Creates a new list resulting of the successive applications of the function ’f’. The ’del’ function is used to delete the content of a node if needed.
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
del: The address of the function used to delete the content of a node if needed.
Return value: The new list. NULL if the allocation fails.
*/

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;//new list
	//t_list	*mirror;
	t_list	*newnode;//node

	if (!lst || !f)
		return (NULL);
	aux = NULL;
	while (lst)
	{
		//function f is associated to each newnode created from lst
		newnode = ft_lstnew((*f)(lst->content));
		if (!newnode)
		{
			//if the node doesn't exist, the list is cleared
			ft_lstclear(&aux, (del));
			return(NULL);
		}
		if (newnode)
			//if the node exist, the node is added at the end of the list
			ft_lstadd_back(&aux, newnode);
		lst = lst->next;
	}
	//the newly created list is returned
	return(aux);
}
