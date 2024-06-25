/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/06/24 22:08:00 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		pipes[2]; // pipes[0] == read | pipes[1] == write
	pid_t	pid[2];
	char	***args;

	args = ft_parser(argc, argv); //parser args
	pid[0] = fork();
	if (pid[0] == -1)
		ft_failure("Fork", 1);
	if (pipe(pipes) == -1) //error
		ft_failure("Pipe", 1);
	if (pid[0] == 0) //child #1
	{
		int fd_in = open(argv[1], O_RDONLY);
		int	fd_temp = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_temp == -1 || fd_in == -1)
			ft_failure("Open", 1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		ft_execve(fd_temp, args[0][0], args[0]);
	}	
	else //parent
	{
		waitpid(pid[0], NULL, 0);
		pid[1] = fork(); // add error
		if (pid[1] == 0) // child #2
		{
			int	fd_temp = open("temp", O_RDONLY);
			if (fd_temp == -1)
				ft_failure("Open", 1);
			close(pipes[0]);			
			dup2(fd_temp, STDIN_FILENO);
			close(fd_temp);			
			ft_execve(pipes[1], args[1][0], args[1]);
		}
		else 
		{
			waitpid(pid[1], NULL, 0);
			close(pipes[1]);
			ft_create_outfile(argv[4], pipes[0]); //WRITE IN OUTFILE
			close(pipes[0]);
			unlink("temp");
			free(args);
		}
	}
	return (0);
}
