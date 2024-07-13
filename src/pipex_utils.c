/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/13 23:41:12 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			{
				while (paths[++i])
					free(paths[i]);
				free(paths);
				return (pathname);
			}
			free(pathname);
			pathname = NULL;
			i++;
		}
	}
	free(pathname);
	free(paths);
	return (NULL);
}

t_cmds	*ft_parser(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*pathname;
	int		i;
	int		n;

	i = 2;
	n = 0;
	cmds = (t_cmds *) malloc((argc - 2) * sizeof(t_cmds));
	if (!cmds)
		ft_error_handler("malloc()", ERROR_MALLOC, NULL, 0);
	while (i < (argc - 1))
	{
		cmds[n].args = ft_split(argv[i], ' ');
		pathname = ft_findpath(envp, cmds[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", cmds[n].args[0]);
		cmds[n].pathname = pathname;
		i++;
		n++;
	}
	cmds[n].args = NULL;
	cmds[n].pathname = NULL;
	return (cmds);
}
