/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:52:10 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/04 23:39:11 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft/libft.h"


#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct 
{
    int open_index;
    int close_index;
    int wait_id;
    int id;
	char **commands;
} t_process_args;

typedef struct 
{
    t_process_args *processes;
    int numb_process;
    int **pipes;
    int state;
} t_main_process;

t_main_process *init_main_process(int count);
void free_main_process(t_main_process *main);
void ft_action_function(t_main_process *main, int id);