/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:33:41 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/21 23:38:50 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*merge(char *s1, char *s2)
{
	char	*merge;

	merge = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (merge);
}

int	ft_heredoc(char *limiter, t_cmds *cmds)
{
	char	*buffer;
	char	*cache;
	int		read_size;
	read_size = 1;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	cache = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	*buffer = 0;
	ft_printf("pipex heredoc> ");
	while (!ft_strnstr(buffer, limiter, ft_strlen(limiter)))
	{
		read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(buffer);
			free(cache);
			return (-1);
		}
		buffer[read_size] = '\0';
		if (ft_strnstr(buffer, limiter, ft_strlen(limiter)))
		{
			char *new_limiter = ft_strjoin(limiter, "\n");
			char *swap = ft_strtrim(buffer, new_limiter);
			cache = merge(cache, swap);
			free(swap);
			free(new_limiter);
			break ;
		}
		cache = merge(cache, buffer);
		if(ft_strchr(buffer, '\n'))
			ft_printf("pipex heredoc> ");
		if (!cache)
			return (-1);
	}
	free(buffer);
	int fd = ft_open(".temp", 2, cmds);	
	write(fd, cache, ft_strlen(cache));
	return (fd);
}
