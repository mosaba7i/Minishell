/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:34:14 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:12:49 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fork_and_run(t_shell *shell, t_command *cmd, t_exec_ctx *ctx)
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
		return (1);
	}
	if (child_pid == 0)
	{
		safe_close(&ctx->pipe_fds[0]);
		run_command_in_child(shell, cmd, *ctx->last_input_fd, ctx->pipe_fds[1]);
	}
	*ctx->started_any_child = 1;
	safe_close(ctx->last_input_fd);
	safe_close(&ctx->pipe_fds[1]);
	*ctx->last_input_fd = ctx->pipe_fds[0];
	*ctx->last_child = child_pid;
	return (0);
}

int	run_one_cmd(t_shell *shell, t_command *cmd, t_exec_ctx *ctx)
{
	ctx->pipe_fds[0] = -1;
	ctx->pipe_fds[1] = -1;
	if (cmd->next && pipe(ctx->pipe_fds) == -1)
	{
		perror("minishell: pipe");
		safe_close(ctx->last_input_fd);
		if (*ctx->started_any_child)
			wait_for_leftovers();
		return (1);
	}
	return (fork_and_run(shell, cmd, ctx));
}
