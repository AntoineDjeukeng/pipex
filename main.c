/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:27:38 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/12 11:34:30 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		i;

	if (!parse_arguments(&px, argc, argv))
		return (1);
	if (!init_pipex(&px, argc, argv, envp))
		return (1);
	if (!create_pipes(&px))
		return (ft_free_pipes(&px, px.n_cmds - 1), 1);
	if (!fork_children(&px))
		return (ft_free_all(&px), 1);
	i = -1;
	while (++i < px.n_cmds - 1)
	{
		close(px.pipes[i][0]);
		close(px.pipes[i][1]);
	}
	i = wait_for_children(px.pids, px.n_cmds);
	if (px.heredoc && access(".heredoc_tmp", F_OK) == 0)
		unlink(".heredoc_tmp");
	ft_free_all(&px);
	return (i);
}
