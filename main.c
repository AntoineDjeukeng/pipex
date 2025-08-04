/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:44:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/04 14:47:39 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int agrc, char *agrv[])
{
	if(agrc>1)
		ft_printf("we are here\n");
	ft_printf("Your name is %s\n",agrv[0]);
	return (0);
}
