/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:37:46 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Deletes and frees the given node and every
successor of that node, using the function ’del’ and free(3).
Finally, the pointer to the list must be set to NULL.
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.
*/

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *aux;
	if (!lst)
		return ;
	while (*lst)
	{
	//copying the node *lst to aux
		aux = *lst;
	//moving to the next node
		*lst = aux->next;
	//deleting the content of the node and free its memory
		ft_lstdelone(aux, (*del));
	}
}
