/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/18 18:06:55 by joneves-         ###   ########.fr       */
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

int	ft_free_paths(char **paths, int i)
{
	while (paths[++i])
		free(paths[i]);
	free(paths);
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

char	*merge(char *s1, char *s2)
{
	char	*merge;

	merge = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (merge);
}

char	*ft_findpath(char **envp, char **cmds)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	if (access(cmds[0], F_OK) == 0 && access(cmds[0], X_OK) == 0)
		return (cmds[0]);
	else if (envp[i])
	{
		while (!ft_strnstr(envp[i], "PATH=", 5))
			i++;
		paths = ft_split(envp[i] + 5, ':');
		i = 0;
		while (paths[i])
		{
			pathname = merge(merge(paths[i], "/"), cmds[0]);
			if (access(pathname, F_OK) == 0 && access(pathname, X_OK) == 0)
				return (ft_free_paths(paths, i), pathname);
			free(pathname);
			pathname = NULL;
			i++;
		}
		free(pathname);
		free(paths);
	}
	return (NULL);
}
