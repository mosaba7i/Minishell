/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:55:20 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/07 09:49:32 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <readline/readline.h>      // readlinne (ext fun)
#include <readline/history.h>       // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay (ext func)
#include <stdio.h>                  // printf, perror, strerror
#include <stdlib.h>                 // malloc, free, exit, getenv
#include <unistd.h>                 // write, read, fork, execve, pipe, dup, dup2, chdir, getcwd, close
#include <fcntl.h>                  // open, O_RDONLY, O_WRONLY, O_CREAT, O_APPEND, O_TRUNC
#include <sys/wait.h>               // wait, waitpid, wait3, wait4
#include <signal.h>                 // signal, sigaction, kill, sigemptyset, sigaddset
#include <dirent.h>                 // opendir, readdir, closedir
#endif

/*ext func like readline can be installed with 
sudo apt-get update
sudo apt-get install libreadline-dev
*/

