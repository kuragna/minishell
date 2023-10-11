/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:24:40 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/10 19:25:04 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cd(const char *path)
{
	int err = chdir(path);
	if (err == -1)
	{
		MS_ERROR("cd: ", path, strerror(errno));
		return 1;
	}
	return 0;
}
