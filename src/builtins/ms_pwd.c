/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:25:40 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/15 17:28:21 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ms_pwd(void)
{
	char	*path = getcwd(NULL, 0);
	if (path == NULL)
	{
		return ms_error("minishell: %s\n", strerror(errno));
	}
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

