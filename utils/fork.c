/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:42:28 by adjeuken          #+#    #+#             */
/*   Updated: 2025/08/04 23:44:40 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void ft_action_function(t_main_process *main, int id)
{
    // Close unrelated pipe ends
    int i = 0;
    while (i <= main->numb_process)
    {
        if (i != id)
            close(main->pipes[i][0]); // not my read
        if (i != id + 1)
            close(main->pipes[i][1]); // not my write
        i++;
    }

    int x;
    if (read(main->pipes[id][0], &x, sizeof(int)) <= 0)
        _exit(1);  // child exits safely

    ft_printf("(Child %d) Got %d\n", id, x);

    // Print the commands for this process
    if (main->processes[id].commands)
    {
        int j = 0;
        ft_printf("(Child %d) Commands:", id);
        while (main->processes[id].commands[j])
        {
            ft_printf(" '%s'", main->processes[id].commands[j]);
            j++;
        }
        ft_printf("\n");
    }

    x++;
    if (write(main->pipes[id+1][1], &x, sizeof(int)) == -1)
        _exit(1);

    ft_printf("(Child %d) Sent %d\n", id, x);

    close(main->pipes[id][0]);
    close(main->pipes[id+1][1]);
    _exit(0);
}
