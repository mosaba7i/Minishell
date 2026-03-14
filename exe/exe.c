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
	if (*fd_to_close != -1)
	{
		close(*fd_to_close);
		*fd_to_close = -1;
	}
}

static int	redirect_fd(int from_fd, int to_fd)
{
	if (from_fd == -1)
		return (-1);
	if (from_fd == to_fd)
		return (0);
	if (dup2(from_fd, to_fd) == -1)
		return (-1);
	return (0);
}

static void	wait_for_leftovers(void)
{
	int	status;

	while (wait(&status) > 0);
}

static int	wait_for_everything(pid_t last_child)
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
				final_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				final_status = WEXITSTATUS(status);
			else
				final_status = 1;
		}
		finished_pid = wait(&status);
	}
	return (final_status);
	return (final_status);
}

static void	child_exit_cleanly(int input_fd, int output_fd,
	char *full_path, char **env_list, int exit_code)
{
	if (input_fd != -1 && input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != -1 && output_fd != STDOUT_FILENO)
		close(output_fd);
	if (full_path)
		free(full_path);
	if (env_list)
		free_strs(env_list);
	exit(exit_code);
}

static void	run_command_in_child(t_shell *shell, t_cmd *command,
	int input_fd, int output_fd)
{
	char	*full_path;
	char	**env_list;

	full_path = NULL;
	env_list = NULL;
	initsig_child();
	if (redirect_fd(input_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		child_exit_cleanly(input_fd, output_fd, full_path, env_list, 1);
	}
	if (redirect_fd(output_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		child_exit_cleanly(input_fd, output_fd, full_path, env_list, 1);
	}
	if (input_fd != -1 && input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != -1 && output_fd != STDOUT_FILENO)
		close(output_fd);
	if (apply_redirs(command->redirs) == -1)
		child_exit_cleanly(-1, -1, full_path, env_list, 1);
	if (!command->args || !command->args[0])
		child_exit_cleanly(-1, -1, full_path, env_list, 0);
	if (is_builtin(command->args[0]))
		child_exit_cleanly(-1, -1, full_path, env_list,
			exe_builtin(shell, command->args));
	full_path = get_cmd_path(shell, command->args[0]);
	if (!full_path)
	{
		write(2, "minishell: ", 11);
		perror(command->args[0]);
		child_exit_cleanly(-1, -1, full_path, env_list, 127);
	}
	env_list = env_to_array(shell->env);
	if (!env_list)
	{
		perror("minishell: env_to_array");
		child_exit_cleanly(-1, -1, full_path, env_list, 1);
	}
	execve(full_path, command->args, env_list);
	perror(command->args[0]);
	if (errno == EACCES)
		child_exit_cleanly(-1, -1, full_path, env_list, 126);
	child_exit_cleanly(-1, -1, full_path, env_list, 126);
}

static int	restore_stdio(int saved_stdin, int saved_stdout)
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

static int	run_builtin_in_parent(t_shell *shell, t_cmd *command)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("minishell: dup");
		safe_close(&saved_stdin);
		safe_close(&saved_stdout);
		return (1);
	}
	builtin_status = 0;
	if (apply_redirs(command->redirs) == -1)
		builtin_status = 1;
	else
		builtin_status = exe_builtin(shell, command->args);
	if (restore_stdio(saved_stdin, saved_stdout))
	{
		perror("minishell: dup2");
		return (1);
	}
	return (builtin_status);
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
		return (shell->exit_status = run_builtin_in_parent(shell,
				command_list));
	last_input_fd = -1;
	last_child = -1;
	started_any_child = 0;
	while (command_list)
	{
		pipe_fds[0] = -1;
		pipe_fds[1] = -1;
		if (command_list->next && pipe(pipe_fds) == -1)
		{
			perror("minishell: pipe");
			safe_close(&last_input_fd);
			if (started_any_child)
				wait_for_leftovers();
			shell->exit_status = 1;
			return (shell->exit_status);
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("minishell: fork");
			safe_close(&last_input_fd);
			safe_close(&pipe_fds[0]);
			safe_close(&pipe_fds[1]);
			if (started_any_child)
				wait_for_leftovers();
			shell->exit_status = 1;
			return (shell->exit_status);
		}
		if (child_pid == 0)
		{
			safe_close(&pipe_fds[0]);
			run_command_in_child(shell, command_list, last_input_fd,
				pipe_fds[1]);
		}
		started_any_child = 1;
		safe_close(&last_input_fd);
		safe_close(&pipe_fds[1]);
		last_input_fd = pipe_fds[0];
		last_child = child_pid;
		command_list = command_list->next;
	}
	safe_close(&last_input_fd);
	shell->exit_status = wait_for_everything(last_child);
	return (shell->exit_status);
}
