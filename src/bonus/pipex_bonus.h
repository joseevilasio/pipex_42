/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:07:30 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/21 23:28:45 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define SUCCESS 0
# define ERROR_ARGUMENTS 2
# define ERROR_FILE_OPEN 3
# define ERROR_FILE_OPEN_OUT 4
# define ERROR_FILE_EXIST_OR_READ 5
# define ERROR_MALLOC 6
# define ERROR_PIPE 7
# define ERROR_FORK 8
# define ERROR_EXECVE 9
# define ERROR_NOT_FOUND 10

# include "../libft/libft.h"
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
	char	*limiter;
	int		end;
}	t_cmds;

int		ft_free_args(t_cmds *cmds);
int		ft_free_paths(char **paths, int i);
int		ft_check(int argc, char **argv);
void	ft_error_handler(char *error, int signal, t_cmds *cmds, int mode);

t_cmds	*ft_parser(int argc, char **argv, char **envp);
int		ft_heredoc(char *limiter, t_cmds *cmds);

int	ft_open(char *pathname, int mode, t_cmds *cmds);

// ref https://www.rozmichelle.com/pipes-forks-dups/

// argv[0]  argv[1]       argv[2]   argv[3]   argv[4]
// ./pipex  "../infile"   cmd       cmd       outfile

//  argv[0]  argv[1]   argv[2]   argv[3]  argv[4]   argv[5]
// ./pipex   here_doc  LIMITER   cmd      cmd1      file

#endif //PIPEX_BONUS_H
