/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:33:41 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/24 23:18:35 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	write_fd(char *str, t_cmds *cmds)
{
	int	fd;

	fd = ft_open(".tmp", 2, cmds);
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		free(str);
		ft_error_handler("write()", ERROR_WRITE, cmds, 0);
	}
	close(fd);
	free(str);
	fd = ft_open(".tmp", 1, cmds);
	return (fd);
}

static char	*get_line(char *buffer, char *limiter, t_cmds *cmds)
{
	char	*cache;
	char	*new_limiter;
	char	*swap;

	cache = (char *) malloc(sizeof(char));
	if (!cache)
	{
		free(buffer);
		ft_error_handler("malloc()", ERROR_MALLOC, cmds, 0);
	}
	*cache = 0;
	if (ft_strnstr(buffer, limiter, ft_strlen(limiter)))
	{
		new_limiter = ft_strjoin(limiter, "\n");
		swap = ft_strtrim(buffer, new_limiter);
		cache = merge(cache, swap);
		free(swap);
		free(new_limiter);
		return (cache);
	}
	cache = merge(cache, buffer);
	if (!cache)
	{
		free(buffer);
		ft_error_handler("read()", ERROR_READ, cmds, 0);
	}
	ft_ //testar com print
	return (cache);
}

static char	*safe_malloc(t_cmds *cmds)
{
	char	*str;

	str = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		ft_error_handler("malloc()", ERROR_MALLOC, cmds, 0);
	*str = 0;
	return (str);
}

int	ft_heredoc(char *limiter, t_cmds *cmds)
{
	char	*buffer;
	char	*cache;
	int		read_size;

	buffer = safe_malloc(cmds);
	read_size = 1;
	ft_printf("pipex heredoc> ");
	while (!ft_strnstr(buffer, limiter, ft_strlen(limiter)))
	{
		read_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(buffer);
			free(cache);
			ft_error_handler("read()", ERROR_READ, cmds, 0);
		}
		buffer[read_size] = '\0';
		cache = get_line(buffer, limiter, cmds);
		if (ft_strnstr(buffer, limiter, ft_strlen(limiter)))
			break ;
		if (ft_strchr(buffer, '\n'))
			ft_printf("pipex heredoc> ");
	}
	free(buffer);
	return (write_fd(cache, cmds));
}
