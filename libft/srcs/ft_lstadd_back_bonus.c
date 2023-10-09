/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:21:25 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: Adds the node ’new’ at the end of the list.
lst: The address of a pointer to the first link of a list.
new: The address of a pointer to the node to be added to the list.
*/

void ft_lstadd_back(t_list **lst, t_list *new)
{ 
	if (!*lst)
	//if the list is empty then lst will take new's value
		*lst = new;
	else
	//else the last node of the chain will take new's value
		ft_lstlast(*lst)-> next = new;
	return ;
}
