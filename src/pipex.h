/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:07:30 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/01 17:43:26 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define SUCCESS 0
# define ERROR_ARGUMENTS 1
# define ERROR_FILE_OPEN 2
# define ERROR_FILE_READ 3
# define ERROR_FILE_WRITE 4
# define ERROR_FILE_EXIST 5
# define ERROR_FILE_EXE 6
# define ERROR_MALLOC 7
# define ERROR_PIPE 8
# define ERROR_FORK 9
# define ERROR_EXECVE 10

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

void	ft_failure(char *str, int mode);
int		ft_create_outfile(char *path, int fd_in);
int		ft_execve(int fd_out, char *pathname, char **args);
void	free_args(char ***args);
int		ft_checkfile(char *pathname);
char 	***ft_parser(char **argv);

#endif //PIPEX_H
