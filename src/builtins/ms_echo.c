/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:23:04 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/12 21:20:52 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_echo(char **input)
{
	// TODO: handle trim space
	// TODO: fix string if has quotes function printing newline
	// TODO: with option -n
	// TODO: trim space from right
	// TODO: handle multiple strings

	//TODO: change char *input to char **input
	//TODO: input received for ms_echo is already cleaned by parsing
	size_t	i = 0;
	size_t	j = 0;

	while (input && input[i][j])
	{
		if (input && *input[j] == MS_DOLLAR)
			*input = getenv(*input + 1);
		else if (input[i][j] == MS_SLASH)
			j++;
		else
			printf("%s ", input[i]);
		i++;
	}
	ft_printf("\n");
}
