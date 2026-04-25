/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:33:33 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 02:33:54 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_close(int *fd_to_close);
void	wait_for_leftovers(void);

int	create_pipe_if_needed(t_command *cmd, int pipe_fds[2])
{
	if (cmd->next && pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	return (0);
}

int	fork_and_handle_error(int *started_any_child, int *last_input_fd,
		int pipe_fds[2], t_shell *shell)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("minishell: fork");
		safe_close(last_input_fd);
		safe_close(&pipe_fds[0]);
		safe_close(&pipe_fds[1]);
		if (*started_any_child)
			wait_for_leftovers();
		shell->exit_status = 1;
		return (-1);
	}
	return (child_pid);
}
