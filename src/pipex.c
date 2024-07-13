/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/13 23:41:12 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *pathname, int mode, t_cmds *cmds)
{
	int	fd;

	if (mode == 1)
	{
		if (access(pathname, F_OK) != 0 && access(pathname, R_OK) != 0
			&& access(pathname, X_OK) != 0)
		{
			perror("open()");
			fd = open("/dev/null", O_RDONLY);
		}
		else
			fd = open(pathname, O_RDONLY);
	}
	if (mode == 2)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_error_handler("open()", ERROR_FILE_OPEN, cmds, 0);
	}
	return (fd);
}

static int	ft_pipex(int fd_in, int fd_out, t_cmds cmds, char **envp)
{
	if (!cmds.pathname)
		fd_in = open("/dev/null", O_RDONLY);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
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

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	pid_t	pid;
	int		fds[2];

	if (argc != 5)
		ft_error_handler(strerror(EINVAL), ERROR_ARGUMENTS, NULL, 1);
	cmds = ft_parser(argc, argv, envp);
	if (pipe(fds) == -1)
		ft_error_handler("pipe()", ERROR_PIPE, cmds, 0);
	pid = fork();
	if (pid == -1)
		ft_error_handler("fork()", ERROR_FORK, cmds, 0);
	if (pid == 0)
	{
		close(fds[0]);
		if (ft_pipex(ft_open(argv[1], 1, cmds), fds[1], cmds[0], envp) == -1)
			ft_error_handler("execve()", ERROR_EXECVE, cmds, 0);
	}
	else
	{
		close(fds[1]);
		if (ft_pipex(fds[0], ft_open(argv[4], 2, cmds), cmds[1], envp) == -1)
			ft_error_handler("execve()", ERROR_EXECVE, cmds, 0);
		wait(NULL);
	}
	return (ft_free_args(cmds));
}
