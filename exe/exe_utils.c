/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:47:42 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:47:43 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_close(int *fd_to_close)
{
	if (*fd_to_close != -1)
	{
		close(*fd_to_close);
		*fd_to_close = -1;
	}
}

void	wait_for_leftovers(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}

static void	print_on_sig(int status)
{
	if (WTERMSIG(status) == SIGINT)
		write(2, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
		ft_fprintf(2, "Quit: (core dumped)\n");
}

int	wait_for_everything(pid_t last_child)
{
	int		status;
	pid_t	finished_pid;
	int		final_status;

	final_status = 0;
	finished_pid = wait(&status);
	while (finished_pid > 0)
	{
		if (finished_pid == last_child)
		{
			if (WIFSIGNALED(status))
			{
				print_on_sig(status);
				final_status = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				final_status = WEXITSTATUS(status);
			else
				final_status = 1;
		}
		finished_pid = wait(&status);
	}
	return (final_status);
}

int	restore_stdio(int saved_stdin, int saved_stdout)
{
	int	restore_failed;

	restore_failed = 0;
	if (saved_stdin != -1)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
			restore_failed = 1;
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			restore_failed = 1;
		close(saved_stdout);
	}
	return (restore_failed);
}
