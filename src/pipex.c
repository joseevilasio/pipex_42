/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/02 12:56:45 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ref https://www.rozmichelle.com/pipes-forks-dups/

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

//utilizar meu printf

int	main(int argc, char **argv)
{
	char	***args;
	pid_t	pid;
	int		fds[2];
	int		fd_in;
	int		fd_out;

	if (argc == 5)
	{
		ft_ensure_file(argv[1]);
		args = ft_parser(argv);
		if (pipe(fds) == -1)
			ft_put_error("pipe()", ERROR_PIPE, args);
		pid = fork();
		if (pid == -1)
			ft_put_error("fork()", ERROR_FORK, args);
		if (pid == 0)
		{
			if ((fd_in = open(argv[1], O_RDONLY)) == -1)
				ft_put_error("open()", ERROR_FILE_OPEN, args);
			close(fds[0]);
			ft_pipex(fd_in, fds[1], args[0][0], args, args[0]);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fds[1]);
			if ((fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
				ft_put_error("open()", ERROR_FILE_OPEN_OUT, args);
			ft_pipex(fds[0], fd_out, args[1][0], args, args[1]);
		}
	}
	else
	{
		printf("%s", strerror(EINVAL));
		exit (ERROR_ARGUMENTS);
	}
	return (0);
}
