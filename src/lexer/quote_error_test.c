/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:59:56 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/24 18:38:29 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

# define SINGLE '\''
# define DOUBLE '\"'

int find_next(char *str, char c)
{
	printf("here\n");
	if (*str && ft_strchr(str, c))
		return (1);
	return (0);
}


int check_quotes(char *str)
{
	size_t	len;
	size_t 	i;
	int		res;

	res = 1;
	i = 0;
	len = ft_strlen(str);
	while (i < len && str[i] != SINGLE && str[i] != DOUBLE)
		i++;
	if (str[i] == SINGLE || str[i] == DOUBLE)
	{
		res = find_next(str + i + 1, str[i]);
	}
	if (!res)
		return  (0);
	else if (str[i] != '\0')
		res = check_quotes(str + i + 2);
	return (res);
}

# if 0

int main()
{
	char *str = readline("$> ");
	int res = check_quotes(str);
	printf("MAIN - res = %d\n", res);
	return (0);
}

#endif
