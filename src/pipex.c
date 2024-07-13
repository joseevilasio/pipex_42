/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/13 21:17:57 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *pathname, int mode, t_cmds *commands)
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
		ft_put_error("open()", ERROR_FILE_OPEN, commands);
	}
	return (fd);
}

static int	ft_pipex(int fd_in, int fd_out, t_cmds commands, char **envp, t_cmds *commands_)
{
	if (!commands.pathname)
		fd_in = open("/dev/null", O_RDONLY);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (commands.pathname)
	{
		if (execve(commands.pathname, commands.args, envp) == -1)
		{
			ft_printf("%s", strerror(ENOENT));
			ft_put_error("execve()", ERROR_EXECVE, commands_);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*commands;
	pid_t	pid;
	int		fds[2];
	int		fd_in;
	int		fd_out;

	if (argc == 5)
	{
		commands = ft_parser(argc, argv, envp);
		fd_in = ft_open(argv[1], 1, commands);
		if (pipe(fds) == -1)
			ft_put_error("pipe()", ERROR_PIPE, commands);
		pid = fork();
		if (pid == -1)
			ft_put_error("fork()", ERROR_FORK, commands);
		if (pid == 0)
		{
			close(fds[0]);
			ft_pipex(fd_in, fds[1], commands[0], envp, commands);
		}
		else
		{
			close(fds[1]);
			fd_out = ft_open(argv[4], 2, commands);
			ft_pipex(fds[0], fd_out, commands[1], envp, commands);
		}
	}
	else
	{
		ft_printf("pipex: %s", strerror(EINVAL));
		exit (ERROR_ARGUMENTS);
	}
	ft_free_args(commands);
	return (0);
}
