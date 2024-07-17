/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/16 23:08:09 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_cmds	*ft_parser(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*pathname;
	int		i;
	int		n;

	i = 2;
	n = 0;
	cmds = (t_cmds *) malloc((argc - 2) * sizeof(t_cmds));
	if (!cmds)
		ft_error_handler("malloc()", ERROR_MALLOC, NULL, 0);
	while (i < (argc - 1))
	{
		cmds[n].args = ft_split(argv[i], ' ');
		pathname = ft_findpath(envp, cmds[n].args);
		if (!pathname)
			ft_printf("pipex: Command not found: %s", cmds[n].args[0]);
		cmds[n].pathname = pathname;
		i++;
		n++;
	}
	cmds[n].args = NULL;
	cmds[n].pathname = NULL;
	return (cmds);
}

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
	pid_t	*pid = malloc ((argc - 3) * sizeof(pid_t));
	int		fds[2];
	int i = 0;

	if (argc < 5)
		ft_error_handler(strerror(EINVAL), ERROR_ARGUMENTS, NULL, 1);
	cmds = ft_parser(argc, argv, envp);
	pid[0] = fork();
	if (pid[0] == -1)
		ft_error_handler("fork()", ERROR_FORK, cmds, 0);
	if (pid[0] == 0)
	{
		ft_printf("Dentro do PID 0\n");
		int fd_in = ft_open(argv[1], 1, cmds);
		while (cmds[i].args)
		{
			if (pipe(fds) == -1)
				ft_error_handler("pipe()", ERROR_PIPE, cmds, 0);
			pid[i + 1] = fork();
			if (pid[i + 1] == -1)
				ft_error_handler("fork()", ERROR_FORK, cmds, 0);
			if (pid[i + 1] == 0)
			{
				ft_printf("Dentro do PID %d -- execute: %s \n", i, cmds[i].args[0]);
				close(fds[0]);
				if (ft_pipex(fd_in, fds[1], cmds[i], envp) == -1)
					ft_error_handler("execve()", ERROR_EXECVE, cmds, 0);
			}
			else
			{
				// waitpid(pid[i + 1], NULL, 0);
				fd_in = ft_open(".tmp", 2, cmds);
				close(fds[1]);
				dup2(fds[0], fd_in);
				close(fds[0]);
			}
			i++;
		}
	}
	else
	{
		waitpid(pid[0], NULL, 0);
		ft_printf("Gerandando dados...");
		// int out = open(fds[0], O_RDONLY);
				char *line = get_next_line(fd_in);
				while (line)
				{
					ft_printf("%s", line);
					line = get_next_line(fd_in);
					line++;		
				}
		
		// close(fds[1]);
		// if (ft_pipex(fds[0], ft_open(argv[4], 2, cmds), cmds[1], envp) == -1)
		// 	ft_error_handler("execve()", ERROR_EXECVE, cmds, 0);
		// unlink(".tmp");
		free(pid);
	}
	return (ft_free_args(cmds));
}

