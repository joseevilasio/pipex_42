/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/08/01 20:42:55 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *pathname, int mode, t_cmds *cmds)
{
	int	fd;

	fd = -1;
	if (mode == 1)
	{
		if (access(pathname, F_OK) != 0 || access(pathname, R_OK) != 0)
		{
			perror("pipex");
			fd = open("/dev/null", O_RDONLY);
		}
		else
			fd = open(pathname, O_RDONLY);
	}
	else if (mode == 2)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_error_handler("pipex", ERROR_FILE_OPEN, cmds, 0);
	}
	return (fd);
}

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
		fd = ft_open(cmds[i].fd_in, 1, cmds);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (i == cmds[0].end)
	{
		fd = ft_open(cmds[i].fd_out, 2, cmds);
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

static void	ft_parent_process(int *fds)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	pid_t	*pid;
	int		fds[2];
	int		i;

	i = 0;
	if (argc != 5)
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
		ft_parent_process(fds);
		i++;
	}
	return (free(pid), ft_free_args(cmds));
}
