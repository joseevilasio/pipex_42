/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:12 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/24 23:13:30 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int		x; //here

	x = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0) //here
		x = 3; //here
	n = 0;
	cmds = (t_cmds *) malloc((argc - 2) * sizeof(t_cmds));
	if (!cmds)
		ft_error_handler("malloc()", ERROR_MALLOC, NULL, 0);
	while ((n + x) < (argc - 1))
	{
		cmds[n].args = ft_split(argv[n + x], ' ');// para here doc aqui n + 3 do contrario n + 2
		pathname = ft_findpath(envp, cmds[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", cmds[n].args[0]);
		cmds[n].pathname = pathname;
		cmds[n].fd_in = argv[1];
		cmds[n].fd_out = argv[argc - 1];
		cmds[n].limiter = argv[2]; //alteracao
		cmds[n].end = argc - (2 + x);
		n++;
	}
	cmds[n].args = NULL;
	cmds[n].pathname = NULL;
	return (cmds);
}
