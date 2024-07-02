/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:31 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/02 18:37:18 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_args(char ***args)
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

int	ft_ensure_file(char *pathname)
{
	if (access(pathname, F_OK) != 0 && access(pathname, R_OK) != 0)
	{
		perror("acess");
		exit (ERROR_FILE_EXIST_OR_READ);
	}
	return (0);
}

void	ft_put_error(char *error, int signal, char ***args)
{
	perror(error);
	ft_free_args(args);
	exit (signal);
}

int	ft_pipex(int fd_in, int fd_out, char *pathname, char ***args, char **args2)
{
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (execve(pathname, args2, 0) == -1)
		ft_put_error("execve()", ERROR_EXECVE, args);
	return (0);
}

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

char	***ft_parser(char **argv)
{
	char	***args;
	char	*temp;

	args = (char ***) malloc(3 * sizeof(char **));
	if (!args)
	{
		perror("malloc()");
		exit (ERROR_MALLOC);
	}
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
