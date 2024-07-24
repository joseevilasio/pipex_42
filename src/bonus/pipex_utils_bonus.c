/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/24 22:45:42 by joneves-         ###   ########.fr       */
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
