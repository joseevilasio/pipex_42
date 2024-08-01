/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/08/01 18:39:01 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_execve(t_cmds cmds, char **envp)
{
	int	fd_in;

	if (!cmds.pathname)
	{
		fd_in = open("/dev/null", O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmds.pathname)
	{
		if (execve(cmds.pathname, cmds.args, envp) == -1)
		{
			ft_printf("%s", strerror(ENOENT));
			return (-1);
		}
	}
	return (0);
}

static void	ft_child_process(int *fds, t_cmds *cmds, int i, char **envp)
{
	int	fd;

	close(fds[0]);
	if (i == 0)
	{
		if (ft_strncmp("here_doc", cmds[0].fd_in, 8) == 0)
			fd = ft_heredoc(cmds[i].limiter, cmds);
		else
			fd = ft_open(cmds[i].fd_in, 1, cmds);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (i == cmds[0].end)
	{
		fd = ft_open(cmds[i].fd_out, cmds[i].mode_outfile, cmds);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	if (ft_execve(cmds[i], envp) == -1)
		ft_error_handler("pipex", ERROR_EXECVE, cmds, 0);
}

static void	ft_parent_process(int *fds, pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	unlink(".tmp");
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	pid_t	*pid;
	int		fds[2];
	int		i;

	i = 0;
	if (ft_check(argc, argv) == -1)
		ft_error_handler(strerror(EINVAL), ERROR_ARGUMENTS, NULL, 1);
	cmds = ft_parser(argc, argv, envp);
	pid = malloc ((argc - 3) * sizeof(pid_t));
	if (!pid)
		ft_error_handler("pipex", ERROR_MALLOC, cmds, 0);
	while (cmds[i].args)
	{
		if (pipe(fds) == -1)
			ft_error_handler("pipex", ERROR_PIPE, cmds, 0);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error_handler("pipex", ERROR_FORK, cmds, 0);
		if (pid[i] == 0)
			ft_child_process(fds, cmds, i, envp);
		ft_parent_process(fds, pid[i]);
		i++;
	}
	return (free(pid), ft_free_args(cmds));
}
