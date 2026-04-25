/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:33:39 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:10:46 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_pipe_error(int *started_any_child, int *last_input_fd,
		int pipe_fds[] __attribute__((unused)), t_shell *shell)
{
	perror("minishell: pipe");
	safe_close(last_input_fd);
	if (*started_any_child)
		wait_for_leftovers();
	shell->exit_status = 1;
	return (-1);
}

static void	setup_child_fork(t_command *cmd, t_exec_ctx *ctx, t_shell *shell)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("minishell: fork");
		safe_close(ctx->last_input_fd);
		safe_close(&ctx->pipe_fds[0]);
		safe_close(&ctx->pipe_fds[1]);
		if (*ctx->started_any_child)
			wait_for_leftovers();
		shell->exit_status = 1;
		return ;
	}
	if (child_pid == 0)
	{
		safe_close(&ctx->pipe_fds[0]);
		run_command_in_child(shell, cmd, *ctx->last_input_fd, ctx->pipe_fds[1]);
	}
	*ctx->started_any_child = 1;
	safe_close(ctx->last_input_fd);
	safe_close(&ctx->pipe_fds[1]);
}

int	execute_loop(t_shell *shell, t_command *cmd_list, t_exec_ctx *ctx)
{
	if (cmd_list->next && pipe(ctx->pipe_fds) == -1)
		return (handle_pipe_error(ctx->started_any_child, ctx->last_input_fd,
				ctx->pipe_fds, shell));
	ctx->pipe_fds[0] = -1;
	ctx->pipe_fds[1] = -1;
	setup_child_fork(cmd_list, ctx, shell);
	*ctx->last_input_fd = ctx->pipe_fds[0];
	*ctx->last_child = *ctx->last_child;
	return (0);
}
