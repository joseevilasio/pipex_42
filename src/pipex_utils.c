/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/13 22:04:09 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_args(t_cmds *cmds)
{
	int	i;
	int	x;

	i = 0;
	while (i != 2)
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
}

void	ft_put_error(char *error, int signal, t_cmds *commands)
{
	ft_free_args(commands);
	perror(error);
	exit (signal);
}

char	*merge(char *s1, char *s2)
{
	char	*merge;

	merge = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (merge);
}


// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

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
	t_cmds	*commands;
	char	*pathname;
	int		i;
	int		n;

	i = 2;
	n = 0;
	commands = (t_cmds *) malloc(3 * sizeof(t_cmds));
	if (!commands)
	{
		perror("malloc()");
		exit (ERROR_MALLOC);
	}
	while (i < (argc - 1))
	{
		commands[n].args = ft_split(argv[i], ' ');
		pathname = ft_findpath(envp, commands[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", commands[n].args[0]);
		commands[n].pathname = pathname;
		i++;
		n++;
	}
	commands[n].args = NULL;
	commands[n].pathname = NULL;
	return (commands);
}
