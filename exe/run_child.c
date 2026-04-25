/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:34:51 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 21:36:44 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_input_fd(int input_fd)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
		close(input_fd);
	}
}

static void	setup_output_fd(int output_fd)
{
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
		close(output_fd);
	}
}

static void	execute_command(t_shell *shell, t_command *cmd, char *path,
		t_child_ctx *ctx)
{
	int	saved_errno;

	(void)shell;
	execve(path, cmd->arg_lst, ctx->env_list);
	saved_errno = errno;
	write(2, "minishell: ", 11);
	if (is_path_directory(path))
		ft_fprintf(2, "%s: Is a directory\n", path);
	else
		perror(cmd->arg_lst[0]);
	if (saved_errno == EACCES)
		child_exit_cleanly(ctx, 126);
	else if (saved_errno == ENOENT)
		child_exit_cleanly(ctx, 127);
	child_exit_cleanly(ctx, 1);
}

static void	handle_path_error(t_shell *shell, t_command *cmd, t_child_ctx *ctx)
{
	(void)shell;
	if (ft_strchr(cmd->arg_lst[0], '/'))
	{
		write(2, "minishell: ", 11);
		perror(cmd->arg_lst[0]);
		if (errno == ENOENT)
			child_exit_cleanly(ctx, 127);
		child_exit_cleanly(ctx, 126);
	}
	print_cmd_not_found(cmd->arg_lst[0]);
	child_exit_cleanly(ctx, 127);
}

void	run_command_in_child(t_shell *shell, t_command *command, int input_fd,
		int output_fd)
{
	t_child_ctx	ctx;

	shell->is_parent = FALSE;
	ctx = (t_child_ctx){input_fd, output_fd, NULL, NULL, shell};
	initsig_child();
	setup_input_fd(input_fd);
	setup_output_fd(output_fd);
	if (apply_redirs(command->redirs) == -1)
		child_exit_cleanly(&ctx, 1);
	if (!command->arg_lst || !command->arg_lst[0])
		child_exit_cleanly(&ctx, 0);
	if (is_builtin(command->arg_lst[0]))
		child_exit_cleanly(&ctx, exe_builtin(shell, command));
	ctx.full_path = get_cmd_path(shell, command->arg_lst[0]);
	if (!ctx.full_path)
		handle_path_error(shell, command, &ctx);
	ctx.env_list = env_to_array(shell->env);
	if (!ctx.env_list)
	{
		perror("minishell: env_to_array");
		child_exit_cleanly(&ctx, 1);
	}
	execute_command(shell, command, ctx.full_path, &ctx);
}
