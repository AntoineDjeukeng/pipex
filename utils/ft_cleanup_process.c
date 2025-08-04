/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:00:56 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/04 23:41:45 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_main_process *init_main_process(int count)
{
    t_main_process *main = malloc(sizeof(t_main_process));
    if (!main)
        return NULL;

    main->numb_process = count;
    main->state = 0;
    main->processes = calloc(count, sizeof(t_process_args));
    if (!main->processes)
        main->state = 1;

    if (main->state == 0)
    {
        main->pipes = calloc(count + 1, sizeof(int *));
        if (!main->pipes)
            main->state = 1;
    }

    int i = 0;
    while (main->state == 0 && i <= count)
    {
        main->pipes[i] = calloc(2, sizeof(int));
        if (!main->pipes[i] || pipe(main->pipes[i]) == -1)
        {
            main->state = 1;
            break;
        }
        i++;
    }

    return main;
}

void free_main_process(t_main_process *main)
{
    if (!main)
        return;

    // Free each process's commands
    if (main->processes)
    {
        int i = 0;
        while (i < main->numb_process)
        {
            if (main->processes[i].commands)
            {
                int j = 0;
                while (main->processes[i].commands[j])
                {
                    free(main->processes[i].commands[j]);
                    j++;
                }
                free(main->processes[i].commands);
            }
            i++;
        }
        free(main->processes);
    }

    // Free pipe memory (no close, already done elsewhere)
    if (main->pipes)
    {
        int i = 0;
        while (i <= main->numb_process)
        {
            if (main->pipes[i])
                free(main->pipes[i]);
            i++;
        }
        free(main->pipes);
    }

    free(main);
}
