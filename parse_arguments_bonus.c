/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:30:28 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/12 11:30:47 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
