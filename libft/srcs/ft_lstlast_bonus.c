/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:35:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Description: returns the last node of the list. lst is the beginning of the list.
*/

t_list *ft_lstlast(t_list *lst)
{
	t_list *t;

//creating a new pointer to lst
	t = lst;
	if (!lst)
		return (NULL);
	while (t)
	{
	//if t -> next doesn't exist, return t
		if (!(t -> next))
			return (t);
		t = t -> next;
	}
	return (t);
}
