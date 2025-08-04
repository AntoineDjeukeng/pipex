/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:44:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/04 23:43:26 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        // fprintf(stderr, "Usage: %s cmd1 [cmd2 ...]\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    t_main_process *main = init_main_process(n);
    if (!main || main->state != 0)
    {
        free_main_process(main);
        return 1;
    }

    // Store commands from arguments
    int i = 1;
    while (i < argc)
    {
        main->processes[i - 1].commands = ft_split(argv[i], ' ');
        i++;
    }

    int start_val = 40;
    // Parent writes the initial value into pipe[0]
    if (write(main->pipes[0][1], &start_val, sizeof(int)) == -1)
    {
        // perror("write");
        free_main_process(main);
        return 1;
    }
    close(main->pipes[0][1]);

    // Fork children
    i = 0;
    while (i < n)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            // perror("fork");
            main->state = 1;
            break;
        }
        if (pid == 0) // child
        {
            ft_action_function(main, i);
        }
        main->processes[i].id = pid;
        i++;
    }

    // Parent: close all pipe ends
    i = 0;
    while (i <= n)
    {
        close(main->pipes[i][0]);
        close(main->pipes[i][1]);
        i++;
    }

    // Wait for children
    i = 0;
    while (i < n)
    {
        wait(NULL);
        i++;
    }

    free_main_process(main);
    return 0;
}
