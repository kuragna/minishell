/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:54:49 by glacroix          #+#    #+#             */
/*   Updated: 2023/10/09 14:01:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It reads from a file descriptor, and stores the read data in a string
 * 
 * @param fd file descriptor
 * @param stash the string that will be returned
 * 
 * @return A pointer to a string.
 */
static char	*ft_read_n_stock(int fd, char *stash)
{
	int		char_read;
	int		i;
	char	buf[BUFFER_SIZE + 1];

	i = 0;
	char_read = 1;
	while (char_read != 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[char_read] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
		while (buf[i] != '\0' && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			return (stash);
	}
	return (stash);
}

/**
 * It searches for the end of a line in the stash, and returns a pointer to the
 * beginning of the line
 * 
 * @param stash the string that contains the line to be returned
 * 
 * @return A pointer to a string.
 */
static char	*search_endline(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/**
 * It moves the position of the stash pointer to the next line
 * 
 * @param stash the string that contains the data that we want to move
 * 
 * @return a pointer to a string.
 */
static char	*move_pos_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	while (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (i < ft_strlen_gnl(stash))
		str[j++] = stash[i++];
	str[j] = '\0';
	free(stash);
	return (str);
}

/**
 * It reads from a file descriptor, and returns a line from it
 * 
 * @param fd the file descriptor
 * 
 * @return A line of text from a file descriptor.
 */
char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = ft_read_n_stock(fd, stash[fd]);
	if (!stash[fd])
	{
		free(stash[fd]);
		return (NULL);
	}
	line = search_endline(stash[fd]);
	stash[fd] = move_pos_stash(stash[fd]);
	return (line);
}

/** invalid fd 
 * multiple fd 
 * read_error.txt*/