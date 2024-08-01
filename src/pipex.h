/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:07:30 by joneves-          #+#    #+#             */
/*   Updated: 2024/08/01 18:22:17 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define SUCCESS 0
# define ERROR_ARGUMENTS 1
# define ERROR_FILE_OPEN 2
# define ERROR_FILE_OPEN_OUT 3
# define ERROR_FILE_EXIST_OR_READ 4
# define ERROR_MALLOC 5
# define ERROR_PIPE 6
# define ERROR_FORK 7
# define ERROR_EXECVE 8
# define ERROR_NOT_FOUND 9

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct t_cmds
{
	char	*pathname;
	char	**args;
	char	*fd_in;
	char	*fd_out;
	int		end;
}	t_cmds;

int		ft_free_args(t_cmds *cmds);
int		ft_free_paths(char **paths, int i);
void	ft_error_handler(char *error, int signal, t_cmds *cmds, int mode);

t_cmds	*ft_parser(int argc, char **argv, char **envp);

// ref https://www.rozmichelle.com/pipes-forks-dups/

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

#endif //PIPEX_H
