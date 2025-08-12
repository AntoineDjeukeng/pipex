/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:28:20 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 16:50:03 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_execve(char *cmd, char **envp, pid_t *pids)
{
	char	**argv_exec;

	if (!cmd || !*cmd)
		ft_error("command not found", cmd, 127, pids);
	argv_exec = malloc(sizeof(char *) * 4);
	if (!argv_exec)
		ft_error("malloc failed", NULL, 1, pids);
	argv_exec[0] = "/bin/sh";
	argv_exec[1] = "-c";
	argv_exec[2] = cmd;
	argv_exec[3] = NULL;
	execve(argv_exec[0], argv_exec, envp);
	free(argv_exec);
	if (errno == ENOENT)
		ft_error("command not found", cmd, 127, pids);
	else if (errno == EACCES)
		ft_error("Permission denied", cmd, 126, pids);
	else
		ft_error("Exec failed", cmd, 1, pids);
}

int	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}

int	setup_heredoc(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	parse_arguments(t_pipex *px, int argc, char **argv)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6))
	{
		ft_print_error(STDERR_FILENO, NULL, "Error: invalid arguments");
		return (0);
	}
	px->heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		px->heredoc = 1;
		px->heredoc_delimiter = argv[2];
		px->cmds = &argv[3];
		px->n_cmds = argc - 4;
	}
	else
	{
		px->heredoc_delimiter = NULL;
		px->cmds = &argv[2];
		px->n_cmds = argc - 3;
	}
	px->outfile = argv[argc - 1];
	return (1);
}
