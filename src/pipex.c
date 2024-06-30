/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/06/29 22:09:13 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		pipes[2]; // pipes[0] == read | pipes[1] == write
	pid_t	pid[2];
	char	***args;

	

	if (argc == 5)
	{
			
		
		// if (!argv[1])
		// {
		// 	if (access(argv[1], F_OK) || access(argv[1], R_OK) || access(argv[1], X_OK))
		// 	{
		// 		perror("acess");
		// 		exit (ERROR_FILE_EXIST);
		// 	}
		// }
		// if (access(argv[1], F_OK) ||
		// 	access(argv[1], R_OK) ||
		// 	access(argv[1], X_OK))
		// {
		// 	perror("acess");
		// 	exit (ERROR_FILE_EXIST);
		// }
		
		args = ft_parser(argc, argv); //parser args
		
		pid[0] = fork();
		if (pid[0] == -1)
		{
			perror("fork");
			free_args(args);
			exit (ERROR_FORK);
		}
		
		if (pid[0] == 0) //child #1
		{
			int fd_in = open(argv[1], O_RDONLY);
			
			if (fd_in == -1)
			{
				perror("open");
				free_args(args);
				exit (ERROR_FILE_OPEN);
			}
			int	fd_temp = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
			
			if (fd_temp == -1)
			{
				perror("open");
				close(fd_in);
				free_args(args);
				exit (ERROR_FILE_OPEN);
			}

			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			
			if (ft_execve(fd_temp, args[0][0], args[0]) == -1)
			{
				free_args(args);
				perror("execve");
				exit (ERROR_EXECVE);
			}
		}	
		else //parent
		{
			waitpid(pid[0], NULL, 0);
			
			pid[1] = fork();

			if (pipe(pipes) == -1) //error
			{
				perror("pipe");
				free_args(args);
				exit (ERROR_PIPE);
			}

			if (pid[1] == -1)
			{
				perror("fork");
				free_args(args);
				exit (ERROR_FORK);
			}

			if (pid[1] == 0) // child #2
			{
				close(pipes[0]);
				close(pipes[1]);
				int	fd_temp = open("temp", O_RDONLY);
				
				if (fd_temp == -1)
				{
					perror("open");
					free_args(args);
					exit (ERROR_FILE_OPEN);
				}

				dup2(fd_temp, STDIN_FILENO);
				close(fd_temp);
					
				if (ft_execve(pipes[1], args[1][0], args[1]) == -1)
				{
					free_args(args);
					perror("execve");
					exit (ERROR_EXECVE);
				}
				
				close(pipes[0]);
				close(pipes[1]);
			}
			else 
			{
				waitpid(pid[1], NULL, 0);
				close(pipes[1]);
				close(pipes[0]);
				
				if (ft_create_outfile(argv[4], pipes[0]) == -1) //WRITE IN OUTFILE
				{
					perror("create");
					free_args(args);
					exit(ERROR_FILE_WRITE);
				}
				
				close(pipes[0]);
				close(pipes[1]);
				unlink("temp");
				free_args(args);
			}
		}
	}
	else
	{
		errno = EINVAL;
		perror("arguments");
		exit (ERROR_ARGUMENTS);
	}
	return (0);
}
