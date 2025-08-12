/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childrens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:33:29 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 15:08:35 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_children_action(int i, t_pipex *px)
{
	if (!setup_stdin(i, px))
		_exit(1);
	if (!setup_stdout(i, px))
		_exit(1);
	close_and_free_pipes(px);
	safe_execve(px->cmds[i], px->envp, px->pids);
}

static int	open_input_fd(t_pipex *px)
{
	int	fd;

	if (px->heredoc)
	{
		fd = setup_heredoc(px->heredoc_delimiter);
		if (fd < 0)
			ft_print_error(STDERR_FILENO, "heredoc", strerror(errno));
	}
	else
	{
		fd = open(px->argv[1], O_RDONLY);
		if (fd < 0)
			ft_print_error(STDERR_FILENO, px->argv[1], strerror(errno));
	}
	return (fd);
}

int	setup_stdin(int i, t_pipex *px)
{
	int	fd_in;

	if (i == 0)
	{
		fd_in = open_input_fd(px);
		if (fd_in < 0)
		{
			free(px->pids);
			close_and_free_pipes(px);
			return (0);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
	}
	return (1);
}

int	setup_stdout(int i, t_pipex *px)
{
	int	fd_out;

	if (i == px->n_cmds - 1)
	{
		if (px->heredoc)
			fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			ft_print_error(STDERR_FILENO, px->outfile, strerror(errno));
			free(px->pids);
			close_and_free_pipes(px);
			return (0);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(px->pipes[i][1], STDOUT_FILENO);
	return (1);
}
