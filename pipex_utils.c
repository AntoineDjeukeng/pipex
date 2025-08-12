/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:25:52 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 14:40:59 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	px->argc = argc;
	px->argv = argv;
	px->envp = envp;
	if (px->heredoc)
	{
		px->n_cmds = argc - 4;
		px->cmds = &argv[3];
	}
	else
	{
		px->n_cmds = argc - 3;
		px->cmds = &argv[2];
	}
	px->pipes = malloc(sizeof(int *) * (px->n_cmds - 1));
	if (!px->pipes)
		return (perror("malloc"), 0);
	return (1);
}

int	create_pipes(t_pipex *px)
{
	int	i;

	i = -1;
	while (++i < px->n_cmds - 1)
	{
		px->pipes[i] = malloc(sizeof(int) * 2);
		if (!px->pipes[i] || pipe(px->pipes[i]) == -1)
			return (perror("pipe"), ft_free_pipes(px, i), 0);
	}
	px->pids = malloc(sizeof(pid_t) * px->n_cmds);
	if (!px->pids)
		return (perror("malloc"), ft_free_pipes(px, px->n_cmds - 1), 0);
	return (1);
}

int	fork_children(t_pipex *px)
{
	int	i;

	i = -1;
	while (++i < px->n_cmds)
	{
		px->pids[i] = fork();
		if (px->pids[i] < 0)
			return (perror("fork"), 0);
		if (px->pids[i] == 0)
			ft_children_action(i, px);
	}
	return (1);
}
