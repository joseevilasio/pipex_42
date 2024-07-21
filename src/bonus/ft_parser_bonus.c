/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:12 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/21 23:36:30 by joneves-         ###   ########.fr       */
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

static char	*ft_findpath(char **envp, char **cmds)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	if (access(cmds[0], F_OK) == 0 && access(cmds[0], X_OK) == 0)
		return (ft_strdup(cmds[0]));
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
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
	free(paths);
	return (NULL);
}

t_cmds	*ft_parser(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*pathname;
	int		n;

	n = 0;
	cmds = (t_cmds *) malloc((argc - 2) * sizeof(t_cmds));
	if (!cmds)
		ft_error_handler("malloc()", ERROR_MALLOC, NULL, 0);
	while ((n + 3) < (argc - 1))
	{
		cmds[n].args = ft_split(argv[n + 3], ' ');// para here doc aqui n + 3 do contrario n + 2
		pathname = ft_findpath(envp, cmds[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", cmds[n].args[0]);
		cmds[n].pathname = pathname;
		cmds[n].fd_in = argv[1];
		cmds[n].fd_out = argv[argc - 1];
		cmds[n].limiter = argv[2]; //alteracao
		cmds[n].end = argc - 4;
		n++;
	}
	cmds[n].args = NULL;
	cmds[n].pathname = NULL;
	return (cmds);
}
