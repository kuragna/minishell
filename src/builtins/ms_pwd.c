/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:25:40 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/10 19:26:05 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ms_pwd(void)
{
	char	*path = getcwd(NULL, 0);
	if (path == NULL)
	{
		MS_ERROR("minishell: ", path, strerror(ENOENT));
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
