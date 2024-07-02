/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/02 20:27:29 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ref https://www.rozmichelle.com/pipes-forks-dups/

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

//resolver para retornar command not found
//refatorar findpath
//refator main

//utilizar meu printf
static int	ft_pipex(int fd_in, int fd_out, t_cmds commands)
{
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (execve(commands.pathname, commands.args, 0) == -1)
		ft_put_error("execve()", ERROR_EXECVE);
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
		ft_ensure_file(argv[1]);
		if (pipe(fds) == -1)
			ft_put_error("pipe()", ERROR_PIPE);
		pid = fork();
		if (pid == -1)
			ft_put_error("fork()", ERROR_FORK);
		commands = ft_parser(argc, argv, envp);
		if (pid == 0) //child
		{
			if ((fd_in = open(argv[1], O_RDONLY)) == -1)
				ft_put_error("open()", ERROR_FILE_OPEN);
			close(fds[0]);
			ft_pipex(fd_in, fds[1], commands[0]);
		}
		else //parent
		{
			close(fds[1]);
			if ((fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
				ft_put_error("open()", ERROR_FILE_OPEN_OUT);
			ft_pipex(fds[0], fd_out, commands[1]);
		}
	}
	else
	{
		printf("%s", strerror(EINVAL));
		exit (ERROR_ARGUMENTS);
	}
	return (0);
}
