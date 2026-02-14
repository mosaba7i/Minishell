/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:09:55 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/07 09:42:32 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



void sighand(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line(); //lifting the pencil and starting on a freshy holyyy linee
    rl_replace_line("",0); //Erase what was being typed, 0 for ctrl+z (don't undo and rem what was being typed)
    rl_redisplay(); // redraws (minishell$ ), buffer, cursor
}

int main(int argc,char **argv)
{
    signal(SIGINT, sighand);
    while (1)
    {
        char *line = readline("minishell$ ");
        if (!line)
            break;
        
        if (strcmp(line, "pwd") == 0)
        {
            int pid;
            pid = fork();
            if (pid == 0)
            {
                execve("/bin/pwd", argv, NULL);
                perror("execve failed");
                exit(0);
            }
            waitpid(pid, NULL, 0);
        }
        
        free(line);
    }

}
