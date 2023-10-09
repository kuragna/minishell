/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:04:54 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given as a parameter 
and free the node. The memory of ’next’ must not be freed.
lst: The node to free.
del: The address of the function used to delete the content.
*/

void ft_lstdelone(t_list *lst, void (*del)(void*))
{	
	if (!lst)
		return ;
//if the node lst exists, we delete the content of the node lst and free its memory
	if (lst)
	{
		del(lst->content);
	}
	free(lst);
	return ;
}
