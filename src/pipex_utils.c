/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/01 18:01:17 by joneves-         ###   ########.fr       */
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

int	ft_create_outfile(char *path, int fd_in)
{
	int		new_fd;
	int		bytes_read;
	int		bytes_write;
	char	*buffer;

	new_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (new_fd < 0)
		return (-1);
	bytes_read = 1;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd_in, buffer, BUFFER_SIZE);
		bytes_write = write(new_fd, buffer, bytes_read);
		if (bytes_read != bytes_write)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	close(new_fd);
	if (bytes_read == -1)
		return (-1);
	return (0);
}

int	ft_execve(int fd_out, char *pathname, char **args)
{
	dup2(fd_out, STDOUT_FILENO); //redireciona a saida (1 - stdout)
	close(fd_out);
	if (execve(pathname, args, 0) == -1) 
		return (-1);
	return (0);
}

int	ft_checkfile(char *pathname)
{
	if (access(pathname, F_OK) != 0)
		ft_failure("acess", 1);
	else if (access(pathname, R_OK) != 0)
		ft_failure("acess", 1);
	return (0);
}

char ***ft_parser(char **argv)
{
	char ***args;
	char *temp;

	// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
	// ./pipex  "../infile"   cmd       cmd       outfile
	args = (char ***) malloc(3 * sizeof(char **));
		if (!args)
		ft_failure("Malloc", 1);
	// ft_checkfile(argv[1]);
	args[0] = ft_split(argv[2], ' ');
	temp = ft_strjoin("/bin/", args[0][0]);
	free(args[0][0]);
	args[0][0] = ft_strdup(temp);
	free(temp);
	args[1] = ft_split(argv[3], ' ');
	temp = ft_strjoin("/bin/", args[1][0]);
	free(args[1][0]);
	args[1][0] = ft_strdup(temp);
	free(temp);
	args[2] = NULL;	
	return (args);
}

void	free_args(char ***args)
{
	int	i;
	int	x;

	i = 0;	
	while (args[i])
	{
		x = 0;
		while (args[i][x])
		{
			free(args[i][x]);
			x++;
		}
		free(args[i]);
		i++;
	}
	free(args);
}


