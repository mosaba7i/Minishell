/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:15:30 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 21:36:44 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_child_fds(t_child_ctx *ctx)
{
	if (ctx->input_fd != -1 && ctx->input_fd != STDIN_FILENO)
		close(ctx->input_fd);
	if (ctx->output_fd != -1 && ctx->output_fd != STDOUT_FILENO)
		close(ctx->output_fd);
}

static void	free_child_paths(t_child_ctx *ctx)
{
	if (ctx->full_path)
		free(ctx->full_path);
	if (ctx->env_list)
		free_strs(ctx->env_list);
}

static void	cleanup_child_shell(t_child_ctx *ctx)
{
	if (ctx->shell)
	{
		free_ptrs(ctx->shell->ptrs->tokens, ctx->shell->ptrs->commands);
		free_env(ctx->shell);
	}
}

void	child_exit_cleanly(t_child_ctx *ctx, int exit_code)
{
	close_child_fds(ctx);
	free_child_paths(ctx);
	cleanup_child_shell(ctx);
	exit(exit_code);
}
