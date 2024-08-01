/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:33:41 by joneves-          #+#    #+#             */
/*   Updated: 2024/08/01 23:14:05 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*safe_malloc(t_cmds *cmds)
{
	char	*str;

	str = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		ft_error_handler("pipex", ERROR_MALLOC, cmds, 0);
	*str = 0;
	return (str);
}

static int	write_fd(char *str, t_cmds *cmds)
{
	int	fd;

	fd = ft_open(".tmp", 2, cmds);
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		free(str);
		ft_error_handler("pipex", ERROR_WRITE, cmds, 0);
	}
	close(fd);
	free(str);
	fd = ft_open(".tmp", 1, cmds);
	return (fd);
}

static char	*join_line(char *before, char *buffer, char *limiter, t_cmds *cmds)
{
	char	*cache;
	char	*new_limiter;
	char	*swap;

	cache = safe_malloc(cmds);
	if (ft_strnstr(buffer, limiter, ft_strlen(buffer))
		&& ft_strlen(buffer) == ft_strlen(limiter) + 1)
	{
		new_limiter = ft_strjoin(limiter, "\n");
		swap = ft_strtrim(buffer, new_limiter);
		cache = merge(before, swap);
		free(swap);
		free(new_limiter);
		return (cache);
	}
	cache = merge(before, buffer);
	if (!cache)
	{
		free(buffer);
		ft_error_handler("pipex", ERROR_READ, cmds, 0);
	}
	return (cache);
}

int	ft_heredoc(char *limiter, t_cmds *cmds)
{
	char	*buffer;
	char	*cache;
	int		read_size;

	buffer = safe_malloc(cmds);
	cache = safe_malloc(cmds);
	ft_printf("pipex heredoc> ");
	while (cache)
	{
		read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(buffer);
			free(cache);
			ft_error_handler("pipex", ERROR_READ, cmds, 0);
		}
		buffer[read_size] = '\0';
		cache = join_line(cache, buffer, limiter, cmds);
		if (ft_strnstr(buffer, limiter, ft_strlen(buffer))
			&& ft_strlen(buffer) == ft_strlen(limiter) + 1)
			break ;
		if (ft_strchr(buffer, '\n'))
			ft_printf("pipex heredoc> ");
	}
	return (free(buffer), write_fd(cache, cmds));
}
