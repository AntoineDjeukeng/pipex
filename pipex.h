/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:33:43 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 16:50:17 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**cmds;
	int		**pipes;
	int		n_cmds;
	char	**envp;
	pid_t	*pids;
	int		heredoc;
	char	*heredoc_delimiter;
	char	*outfile;
	int		in_fd;
	int		out_fd;
}			t_pipex;

void		ft_error(const char *msg, const char *detail, int exit_code,
				pid_t *pids);
void		safe_execve(char *cmd, char **envp, pid_t *pids);
int			wait_for_children(pid_t *pids, int count);
void		close_and_free_pipes(t_pipex *px);
int			setup_stdout(int i, t_pipex *px);
int			setup_stdin(int i, t_pipex *px);
void		ft_children_action(int i, t_pipex *px);
int			fork_children(t_pipex *px);
int			create_pipes(t_pipex *px);
int			init_pipex(t_pipex *px, int argc, char **argv, char **envp);
void		ft_free_all(t_pipex *px);
void		ft_free_pipes(t_pipex *px, int count);
void		ft_print_error(int fd, char *context, char *msg);
int			setup_heredoc(const char *delimiter);
int	setup_heredoc(const char *delimiter);
int	parse_arguments(t_pipex *px, int argc, char **argv);