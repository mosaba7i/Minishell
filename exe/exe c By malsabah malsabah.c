/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:00:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/10 16:51:48 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	safe_close(int *fd_to_close)
{
	// if fd is validd close it and reset it to -1
}

static int	redirect_fd(int from_fd, int to_fd)
{
	//  return error if from_fd is invalid
	//     if from_fd == to_fd, do nothing
	//  otherwise call dup2(from_fd, to_fd)
	return (0);
}

static void	wait_for_leftovers(void)
{
	int	status;

	// keep calling wait() until there are no children left
}

static int	wait_for_everything(pid_t last_child)
{
	int		status;
	pid_t	finished_pid;
	int		final_status;

	//    waiting   for all children
	// save exit status only for the lats child in the pipeline
	return (final_status);
}

static void	child_exit_cleanly(int input_fd, int output_fd,
	char *full_path, char **env_list, int exit_code)
{
	// close input and output fdss if needed ofc 
	// free   path and env array if allocated
	//   exit with exit_code
	exit(exit_code);
}

static void	run_command_in_child(t_shell *shell, t_cmd *command,
	int input_fd, int output_fd)
{
	// initt child signals
	// dup input_fd to stdin if needed
	// dup output_fd to stdout if needed
	// apply redirs
	// if empty command -> exit(0)
	// if builtin -> run builtin and exit with its return value
	// resolve da full exec path
	// convert env list to envp array
	// call execve
	// on error cleanup and exit with a good written good 
}

static int	restore_stdio(int saved_stdin, int saved_stdout)
{
	// restore original stdin and stdout with dup2
	// close saved   copies
	return (0);
}

static int	run_builtin_in_parent(t_shell *shell, t_cmd *command)
{
	// save  stdin stdout
	// apply redirs
	// run builtin  in parent
	// restore stdin and stdout
	return (0);
}

int	execute(t_shell *shell, t_cmd *command_list)
{
	int		last_input_fd;
	int		pipe_fds[2];
	pid_t	child_pid;
	pid_t	last_child;
	int		started_any_child;

	if (!command_list)
		return (0);
	if (!command_list->next && command_list->args
		&& is_builtin(command_list->args[0]))
	{
		// run the single builtin in parent
	}
	last_input_fd = -1;
	last_child = -1;
	started_any_child = 0;
	while (command_list)
	{
		pipe_fds[0] = -1;
		pipe_fds[1] = -1;
		// if there is a next cmd makee a pipe
		// fork a  child
		// child: run current command with proper input and output
		// parent  close unused fds and move to next command
		command_list = command_list->next;
	}
	// close any leftover  fd
	// wait for children
	return (shell->exit_status);
}
