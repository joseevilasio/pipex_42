/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 23:25:01 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/07 16:07:33 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*merge(char *s1, char *s2)
{
	char	*merge;

	if (!*s1 && !*s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	merge = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (merge);
}

static char	*putcache(char *cache)
{
	char	*new_cache;

	if (!cache)
		return (NULL);
	if (!ft_strchr(cache, '\n'))
	{
		free(cache);
		return (NULL);
	}
	new_cache = ft_strdup(ft_strchr(cache, '\n') + 1);
	if (!new_cache)
	{
		free(cache);
		return (NULL);
	}
	free(cache);
	return (new_cache);
}

static char	*putline(char *cache)
{
	char	*line;
	size_t	size;

	if (!cache)
		return (NULL);
	if (!*cache)
	{
		free(cache);
		return (NULL);
	}
	if (!ft_strchr(cache, '\n'))
		size = ft_strlen(cache);
	else
		size = ft_strlen(cache) - ft_strlen(ft_strchr(cache, '\n') + 1);
	line = (char *) malloc((size + 1) * sizeof(char));
	if (!line)
	{
		free(cache);
		return (NULL);
	}
	ft_strlcpy(line, cache, size + 1);
	return (line);
}

static char	*read_fd(int fd, char *cache)
{
	char	*buffer;
	int		read_size;

	read_size = 1;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	while (!ft_strchr(buffer, '\n') && read_size != 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(buffer);
			free(cache);
			return (NULL);
		}
		buffer[read_size] = '\0';
		cache = merge(cache, buffer);
		if (!cache)
			return (NULL);
	}
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*cache;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!cache)
	{
		cache = NULL;
		cache = (char *) malloc(sizeof(char));
		if (!cache)
			return (NULL);
		*cache = 0;
	}
	cache = read_fd(fd, cache);
	line = putline(cache);
	cache = putcache(cache);
	return (line);
}
