/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/25 22:28:01 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_free_args(t_cmds *cmds)
{
	int	i;
	int	x;

	i = 0;
	while (cmds[i].args)
	{
		x = 0;
		while (cmds[i].args[x])
		{
			free(cmds[i].args[x]);
			x++;
		}
		free(cmds[i].args);
		free(cmds[i].pathname);
		i++;
	}
	free(cmds);
	return (0);
}

void	ft_error_handler(char *error, int signal, t_cmds *cmds, int mode)
{
	if (mode == 0)
	{
		if (cmds)
			ft_free_args(cmds);
		perror(error);
		exit (signal);
	}
	else
	{
		ft_printf("pipex: %s", error);
		exit (signal);
	}
}

int	ft_check(int argc, char **argv)
{
	if (argc == 6 && ft_strncmp("here_doc", argv[1], 8) == 0)
		return (0);
	else if (argc < 5)
		return (-1);
	return (0);
}

char	*merge(char *s1, char *s2)
{
	char	*merge;

	merge = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (merge);
}

int	ft_open(char *pathname, int mode, t_cmds *cmds)
{
	int	fd;

	if (mode == 1)
	{
		if (access(pathname, F_OK) != 0 || access(pathname, R_OK) != 0)
		{
			perror("access()");
			fd = open("/dev/null", O_RDONLY);
		}
		else
			fd = open(pathname, O_RDONLY);
	}
	else if (mode == 2)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 3)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_error_handler("open()", ERROR_FILE_OPEN, cmds, 0);
	}
	return (fd);
}
