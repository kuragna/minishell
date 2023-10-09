/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:48:13 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Allocates with malloc and returns a new node. The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable ’next’ is initialized to NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list *node;

	//creating a new node and allocating memory to it
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	//content of the present node
	node -> content = content;
	//next node is NULL
	node -> next = NULL;
	//returning node
	return (node);
}
