/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:32:42 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/07 16:43:08 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(int fd, char *context, char *msg)
{
	ft_putstr_fd("pipex: ", fd);
	if (context)
	{
		ft_putstr_fd(context, fd);
		ft_putstr_fd(": ", fd);
	}
	if (msg)
		ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_error(const char *msg, const char *detail, int exit_code,
		pid_t *pids)
{
	if (detail)
		ft_print_error(STDERR_FILENO, (char *)detail, strerror(errno));
	else
		ft_print_error(STDERR_FILENO, NULL, (char *)msg);
	if (pids)
		free(pids);
	_exit(exit_code);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
