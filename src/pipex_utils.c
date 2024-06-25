/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/06/24 21:54:07 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_failure(char *str, int mode)
{
	if (mode == 1)
	{
		perror(str);
		exit (1);
	}
	else
	{
		printf("%s", str);
		exit (1);
	}
}

void	ft_create_outfile(char *path, int fd_in)
{
	int		new_fd;
	int		bytes_read;
	int		bytes_write;
	char	*buffer;

	new_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (new_fd < 0)
		ft_failure("Open file", 1);
	bytes_read = 1;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		ft_failure("Malloc", 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd_in, buffer, BUFFER_SIZE);
		bytes_write = write(new_fd, buffer, bytes_read);
		if (bytes_read != bytes_write)
		{
			free(buffer);
			ft_failure("Write", 1);
		}
	}
	free(buffer);
	close(new_fd);
	if (bytes_read == -1)
		ft_failure("Read", 1);
}

void	ft_execve(int fd_out, char *pathname, char **args)
{
	dup2(fd_out, STDOUT_FILENO); //redireciona a saida (1 - stdout)
	close(fd_out);
	if (execve(pathname, args, 0) == -1) 
	{
		perror("execve");
		exit(1);
	}
}

int	ft_checkfile(char *pathname)
{
	if (access(pathname, F_OK) != 0)
		ft_failure("Open file", 1);
	else if (access(pathname, R_OK) != 0)
		ft_failure("Read file", 1);
	return (0);
}

char ***ft_parser(int argc, char **argv)
{
	char ***args;
	// char **split;

	// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
	// ./pipex  "../infile"   cmd       cmd       outfile
	if (argc == 5)
	{
		args = (char ***) malloc(3 * sizeof(char **));
		if (!args)
			ft_failure("Malloc", 1);
		ft_checkfile(argv[1]);
		args[0] = ft_split(argv[2], ' ');
		args[0][0] = ft_strjoin("/bin/", args[0][0]);
		args[1] = ft_split(argv[3], ' ');
		args[1][0] = ft_strjoin("/bin/", args[1][0]);
		args[2] = NULL;
	}
	else
	{
		ft_failure("Erro arguments", 2);
		return (NULL);
	}
	return (args);
}
