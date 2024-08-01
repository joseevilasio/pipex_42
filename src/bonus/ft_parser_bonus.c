/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:12 by joneves-          #+#    #+#             */
/*   Updated: 2024/08/01 23:21:34 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_free_paths(char **paths, int i)
{
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

static char	*ft_findpath(char **envp, char **cmds)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	paths = NULL;
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
		i++;
	}
	free(paths);
	return (NULL);
}

static void	setup_cmds(t_cmds *cmds)
{
	cmds->pathname = NULL;
	cmds->args = NULL;
	cmds->fd_in = NULL;
	cmds->fd_out = NULL;
	cmds->limiter = NULL;
	cmds->end = 0;
	cmds->mode_outfile = 0;
}

static int	is_heredoc(char *argument)
{
	if (ft_strncmp("here_doc", argument, 8) == 0)
		return (3);
	else
		return (2);
}

t_cmds	*ft_parser(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*pathname;
	int		n;

	n = 0;
	cmds = (t_cmds *) malloc((argc - 2) * sizeof(t_cmds));
	if (!cmds)
		ft_error_handler("pipex", ERROR_MALLOC, NULL, 0);
	while ((n + is_heredoc(argv[1])) < (argc - 1))
	{
		cmds[n].args = ft_split(argv[n + is_heredoc(argv[1])], ' ');
		pathname = ft_findpath(envp, cmds[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", cmds[n].args[0]);
		cmds[n].pathname = pathname;
		cmds[n].fd_in = argv[1];
		cmds[n].fd_out = argv[argc - 1];
		cmds[n].limiter = argv[2];
		cmds[n].end = argc - (2 + is_heredoc(argv[1]));
		cmds[n].mode_outfile = is_heredoc(argv[1]);
		n++;
	}
	setup_cmds(&cmds[n]);
	return (cmds);
}
