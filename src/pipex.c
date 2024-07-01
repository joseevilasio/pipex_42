/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:44:40 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/01 20:51:11 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	print_fd(int fd)
// {
// 	int		bytes_read;
// 	char	*buffer;

// 	bytes_read = 1;
// 	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	printf("%s", buffer);
// 	free(buffer);
// }

// static int	copy_paste(int fd_out, int fd_in)
// {
// 	int		bytes_read;
// 	int		bytes_write;
// 	char	*buffer;

// 	bytes_read = 1;
// 	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (-1);
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = read(fd_in, buffer, BUFFER_SIZE);
// 		bytes_write = write(fd_out, buffer, bytes_read);
// 		if (bytes_read != bytes_write)
// 		{
// 			free(buffer);
// 			return (-1);
// 		}
// 	}
// 	free(buffer);
// 	if (bytes_read == -1)
// 		return (-1);
// 	return (0);
// }

// static int	create_pipes(int **pipes)
// {
// 	int n;
	
// 	n = 0;
// 	while (n < 2)
// 	{	
// 		if (pipe(pipes[n]) == -1)
// 		{
// 			perror("pipe");
// 			free_args(args);
// 			exit (ERROR_PIPE);
// 		}
// 		n++;
// 	}
// 	return (0);
// }


// ref https://www.rozmichelle.com/pipes-forks-dups/

int	main(int argc, char **argv)
{
	int		pipes[2][2]; // pipes[0] == read | pipes[1] == write
	pid_t	pid[2];

	if (argc == 5)
	{

		if (access(argv[1], F_OK) || access(argv[1], R_OK) || access(argv[1], X_OK))
		{
			perror("acess");
			exit (ERROR_FILE_EXIST);
		}

		char	***args = ft_parser(argv); //parser args
		int n;
	
		n = 0;
		while (n < 2)
		{	
			if (pipe(pipes[n]) == -1)
			{
				perror("pipe");
				free_args(args);
				exit (ERROR_PIPE);
			}
			n++;
		}
		
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
			
			close(pipes[0][0]);
			close(pipes[1][0]);
			close(pipes[1][1]);

			dup2(fd_in, STDIN_FILENO); // redireciona content para stdin
			close(fd_in);

			dup2(STDOUT_FILENO, pipes[0][1]); //redireciona content para pipe #1			
			close(pipes[0][1]);
			
			if (execve(args[0][0], args[0], 0) == -1)
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

			if (pid[1] == -1)
			{
				perror("fork");
				free_args(args);
				exit (ERROR_FORK);
			}

			if (pid[1] == 0) // child #2
			{
				close(pipes[0][1]);
				close(pipes[1][0]);
				
				dup2(pipes[0][0], STDIN_FILENO);
				dup2(pipes[1][1], STDOUT_FILENO);
				
				close(pipes[0][0]);
				close(pipes[1][1]);

				if (execve(args[1][0], args[1], 0) == -1)
				{
					free_args(args);
					perror("execve");
					exit (ERROR_EXECVE);
				}

			}
			else 
			{
				waitpid(pid[1], NULL, 0);
				
				close(pipes[0][0]);
				close(pipes[0][1]);
				close(pipes[1][1]);

				if (ft_create_outfile(argv[4], pipes[1][0]) == -1) //WRITE IN OUTFILE
				{
					perror("create");
					free_args(args);
					exit(ERROR_FILE_WRITE);
				}
				
				close(pipes[1][0]);
				// close(pipes[1]);
				// unlink("temp");
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
