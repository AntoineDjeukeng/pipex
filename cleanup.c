/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:00:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/06 23:29:07 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_and_free_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->n_cmds - 1)
	{
		close(px->pipes[i][0]);
		close(px->pipes[i][1]);
		free(px->pipes[i]);
		i++;
	}
	free(px->pipes);
}

void	ft_free_pipes(t_pipex *px, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (px->pipes[i])
			free(px->pipes[i]);
		i++;
	}
	free(px->pipes);
}

void	ft_free_all(t_pipex *px)
{
	ft_free_pipes(px, px->n_cmds - 1);
	free(px->pids);
}
