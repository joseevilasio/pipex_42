/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:07:30 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/02 12:48:51 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define SUCCESS 0
# define ERROR_ARGUMENTS 2
# define ERROR_FILE_OPEN 3
# define ERROR_FILE_OPEN_OUT 4
# define ERROR_FILE_EXIST_OR_READ 5
# define ERROR_MALLOC 6
# define ERROR_PIPE 7
# define ERROR_FORK 8
# define ERROR_EXECVE 9

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

int		ft_ensure_file(char *pathname);
int		ft_pipex(int fd_in, int fd_out, char *pathname, char ***args, char **args2);
void	ft_free_args(char ***args);
void	ft_put_error(char *error, int signal, char ***args);
char	***ft_parser(char **argv);

#endif //PIPEX_H
