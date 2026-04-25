/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:00:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 02:33:27 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* redirect and child cleanup are handled in exe/run_child.c now */

void	print_cmd_not_found(char *cmd)
{
	char	*tmp;
	char	*msg;

	if (ft_strcmp(cmd, "") == 0)
	{
		write(2, " '' : command not found\n", 24);
		return ;
	}
	tmp = ft_strjoin(cmd, ": ");
	if (!tmp)
		return ;
	msg = ft_strjoin(tmp, "command not found\n");
	free(tmp);
	if (!msg)
		return ;
	write(2, msg, ft_strlen(msg));
	free(msg);
}

/* run_command_in_child moved to exe/run_child.c */

static int	save_stdio(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		safe_close(saved_stdin);
		safe_close(saved_stdout);
		return (1);
	}
	return (0);
}

static int	run_builtin_in_parent(t_shell *shell, t_command *command)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_status;

	shell->is_parent = TRUE;
	if (command->arg_lst && ft_strncmp(command->arg_lst[0], "exit", 5) == 0)
	{
		if (apply_redirs(command->redirs) == -1)
			return (1);
		return (exe_builtin(shell, command));
	}
	if (save_stdio(&saved_stdin, &saved_stdout))
		return (1);
	builtin_status = apply_and_exec_builtin(shell, command);
	if (restore_stdio(saved_stdin, saved_stdout))
		return (1);
	return (builtin_status);
}

int	execute(t_shell *shell, t_command *command_list)
{
	initsig_parent();
	if (!command_list)
		return (0);
	if (!command_list->next && command_list->arg_lst
		&& is_builtin(command_list->arg_lst[0]))
		return (shell->exit_status = run_builtin_in_parent(shell,
				command_list));
	shell->exit_status = run_pipeline(shell, command_list);
	return (shell->exit_status);
}
