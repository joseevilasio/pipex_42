/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/02 20:20:20 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_args(char ***args)
{
	int	i;
	int	x;

	i = 0;
	while (args[i])
	{
		x = 0;
		while (args[i][x])
		{
			free(args[i][x]);
			x++;
		}
		free(args[i]);
		i++;
	}
	free(args);
}

int	ft_ensure_file(char *pathname)
{
	if (access(pathname, F_OK) != 0 && access(pathname, R_OK) != 0
		&& access(pathname, X_OK) != 0)
	{
		perror("acess");
		exit (ERROR_FILE_EXIST_OR_READ);
	}
	return (0);
}

void	ft_put_error(char *error, int signal)
{
	perror(error);
	exit (signal);
}

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

char	*ft_findpath(char **envp, char **cmds)
{
	char	**paths;
	char	*tmp;
	char	*pathname;
	char	*envs;
	int		i;

	i = 0;
	while (envp[i])
	{
		envs = ft_strnstr(envp[i], "PATH=", 5);
		if (envs)
		{
			i = 0;
			paths = ft_split(envs + 5, ':');
			while(paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				pathname = ft_strjoin(tmp, cmds[0]);
				free(tmp);
				free(paths[i]);
				if (access(pathname, F_OK) == 0 && access(pathname, X_OK) == 0)
				{
					while(paths[i])
						free(paths[++i]);
					free(paths);
					return (pathname);
				}
				i++;
			}
			return ("");
		}
		i++;
	}
	return (NULL);
}

t_cmds	*ft_parser(int argc, char **argv, char **envp)
{
	t_cmds	*commands;
	int		i;
	int		n;

	i = 2;
	n = 0;
	commands = malloc((argc - 3) * sizeof(t_cmds));
	if (!commands)
	{
		perror("malloc()");
		exit (ERROR_MALLOC);
	}
	while (i < (argc - 1))
	{
		commands[n].args = ft_split(argv[i], ' ');
		commands[n].pathname = ft_findpath(envp, commands[n].args);
		i++;
		n++;
	}
	return (commands);
}
